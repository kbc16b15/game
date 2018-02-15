#include "stdafx.h"
#include "SoundEngine.h"
#include "WaveFile.h"
#include "Sound.h"

SoundEngine *SoundEngine::m_soundEngine = NULL;

#define NUM_PRESETS 30

namespace {
	//マイクロソフトのサンプルから引っ張ってきたサウンドコーン。
	// Specify sound cone to add directionality to listener for artistic effect:
	// Emitters behind the listener are defined here to be more attenuated,
	// have a lower LPF cutoff frequency,
	// yet have a slightly higher reverb send level.
	static const X3DAUDIO_CONE Listener_DirectionalCone = { X3DAUDIO_PI*5.0f / 6.0f, X3DAUDIO_PI*11.0f / 6.0f, 1.0f, 0.75f, 0.0f, 0.25f, 0.708f, 1.0f };

	// Specify LFE level distance curve such that it rolls off much sooner than
	// all non-LFE channels, making use of the subwoofer more dramatic.
	static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_LFE_CurvePoints[3] = { 0.0f, 1.0f, 0.25f, 0.0f, 1.0f, 0.0f };
	static const X3DAUDIO_DISTANCE_CURVE       Emitter_LFE_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_LFE_CurvePoints[0], 3 };

	// Specify reverb send level distance curve such that reverb send increases
	// slightly with distance before rolling off to silence.
	// With the direct channels being increasingly attenuated with distance,
	// this has the effect of increasing the reverb-to-direct sound ratio,
	// reinforcing the perception of distance.
	static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_Reverb_CurvePoints[3] = { 0.0f, 0.5f, 0.75f, 1.0f, 1.0f, 0.0f };
	static const X3DAUDIO_DISTANCE_CURVE       Emitter_Reverb_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_Reverb_CurvePoints[0], 3 };

	XAUDIO2FX_REVERB_I3DL2_PARAMETERS PRESET_PARAMS[NUM_PRESETS] =
	{
		XAUDIO2FX_I3DL2_PRESET_FOREST,
		XAUDIO2FX_I3DL2_PRESET_DEFAULT,
		XAUDIO2FX_I3DL2_PRESET_GENERIC,
		XAUDIO2FX_I3DL2_PRESET_PADDEDCELL,
		XAUDIO2FX_I3DL2_PRESET_ROOM,
		XAUDIO2FX_I3DL2_PRESET_BATHROOM,
		XAUDIO2FX_I3DL2_PRESET_LIVINGROOM,
		XAUDIO2FX_I3DL2_PRESET_STONEROOM,
		XAUDIO2FX_I3DL2_PRESET_AUDITORIUM,
		XAUDIO2FX_I3DL2_PRESET_CONCERTHALL,
		XAUDIO2FX_I3DL2_PRESET_CAVE,
		XAUDIO2FX_I3DL2_PRESET_ARENA,
		XAUDIO2FX_I3DL2_PRESET_HANGAR,
		XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY,
		XAUDIO2FX_I3DL2_PRESET_HALLWAY,
		XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR,
		XAUDIO2FX_I3DL2_PRESET_ALLEY,
		XAUDIO2FX_I3DL2_PRESET_CITY,
		XAUDIO2FX_I3DL2_PRESET_MOUNTAINS,
		XAUDIO2FX_I3DL2_PRESET_QUARRY,
		XAUDIO2FX_I3DL2_PRESET_PLAIN,
		XAUDIO2FX_I3DL2_PRESET_PARKINGLOT,
		XAUDIO2FX_I3DL2_PRESET_SEWERPIPE,
		XAUDIO2FX_I3DL2_PRESET_UNDERWATER,
		XAUDIO2FX_I3DL2_PRESET_SMALLROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMROOM,
		XAUDIO2FX_I3DL2_PRESET_LARGEROOM,
		XAUDIO2FX_I3DL2_PRESET_MEDIUMHALL,
		XAUDIO2FX_I3DL2_PRESET_LARGEHALL,
		XAUDIO2FX_I3DL2_PRESET_PLATE,
	};
}
SoundEngine::SoundEngine()
{
	//memset(m_hx3DAudio, 0, sizeof(m_hx3DAudio));
}


SoundEngine::~SoundEngine()
{
	Release();
}


void SoundEngine::Init()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	unsigned int flags = 0;
#ifdef _DEBUG
	flags |= XAUDIO2_DEBUG_ENGINE;
#endif
	//XAUDIO2を初期化。
	HRESULT hr;
	if (FAILED(hr = XAudio2Create(&m_xAudio2, flags)))
	{
		//return;
	}
	//マスターボリュームの作成。
	if (FAILED(hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice)))
	{
		Release();
		return;
	}
	//サウンドデバイスの情報を取得。
	XAUDIO2_DEVICE_DETAILS details;
	if (FAILED(hr = m_xAudio2->GetDeviceDetails(0, &details)))
	{
		Release();
		return;
	}

	if (details.OutputFormat.Format.nChannels > OUTPUTCHANNELS)
	{
		Release();
		return;
	}

	m_channelMask = details.OutputFormat.dwChannelMask;
	m_nChannels = details.OutputFormat.Format.nChannels;

	//リバーブエフェクトを作成。
	flags = 0;
#ifdef _DEBUG
	flags |= XAUDIO2FX_DEBUG;
#endif
	if (FAILED(hr = XAudio2CreateReverb(&m_reverbEffect, flags))) {
		Release();
		return;
	}
	//サブミックスボイスを作成。
	XAUDIO2_EFFECT_DESCRIPTOR effects[] = { { m_reverbEffect, TRUE, 1 } };
	XAUDIO2_EFFECT_CHAIN effectChain = { 1, effects };

	if (FAILED(hr = m_xAudio2->CreateSubmixVoice(&m_submixVoice, 1,
		details.OutputFormat.Format.nSamplesPerSec, 0, 0,
		NULL, &effectChain)))
	{
		Release();
		return;
	}
	//デフォルトのFXパラメータを設定。
	XAUDIO2FX_REVERB_PARAMETERS native;
	ReverbConvertI3DL2ToNative(&PRESET_PARAMS[0], &native);
	m_submixVoice->SetEffectParameters(0, &native, sizeof(native));

	//初期化完了。
	m_isInited = true;
}
/*!
* @brief	開放。
*/
void SoundEngine::Release()
{
	//波形データバンクを解放。
	m_waveFileBank.ReleaseAll();
	if (m_submixVoice != nullptr) {
		m_submixVoice->DestroyVoice();
		m_submixVoice = nullptr;
	}
	if (m_reverbEffect != nullptr) {
		m_reverbEffect->Release();
		m_reverbEffect = nullptr;
	}
	if (m_masteringVoice != nullptr) {
		m_masteringVoice->DestroyVoice();
		m_masteringVoice = nullptr;
	}

	if (m_xAudio2 != nullptr) {
		m_xAudio2->Release();
		m_xAudio2 = nullptr;
	}

	CoUninitialize();

}
/*!
* @brief	XAudio2のソースボイスを作成。
*/
IXAudio2SourceVoice* SoundEngine::CreateXAudio2SourceVoice(WaveFile* waveFile, bool is3DSound)
{
	//XAudio2Create(&m_xAudio2, 0);
	//m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	IXAudio2SourceVoice* pSourceVoice;
	if (is3DSound == false) {
		//2Dサウンド。
		if (FAILED(m_xAudio2->CreateSourceVoice(&pSourceVoice, waveFile->GetFormat())))
		{
			return nullptr;
		}
	}
	else {

		return nullptr;
	}

	return pSourceVoice;
}
/*!
* @brief	更新。
*/
void SoundEngine::Update()
{
	if (!m_isInited) {
		return;
	}

}