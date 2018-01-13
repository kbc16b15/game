#include "stdafx.h"
#include "SoundEngine.h"
#include "WaveFile.h"
#include "Sound.h"

#define NUM_PRESETS 30
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
		return;
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
	XAudio2Create(&m_xAudio2, 0);
	m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
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