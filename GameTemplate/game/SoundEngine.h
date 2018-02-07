#pragma once
#include "WaveFileBank.h"
#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//最大出力チャンネル数。
class SoundEngine
{
public:
	~SoundEngine();

	//class CWaveFile;
	//class CSoundSource;
	/*!
	* @brief	初期化。
	*/
	void Init();
	/*!
	* @brief	開放。
	*/
	void Release();
	/*!
	* @brief	更新。
	*/
	void Update();
	
	/*!
	* @brief	XAudio2のソースボイスを作成。
	*/
	IXAudio2SourceVoice* CreateXAudio2SourceVoice(WaveFile* waveFile, bool is3DSound);
	IXAudio2MasteringVoice* GetMasteringVoice()
	{
		return m_masteringVoice;
	}
	IXAudio2SubmixVoice* GetSubmixVoice()
	{
		return m_submixVoice;
	}
	/*!
	* @brief	出力チャンネルの数を取得。
	*/
	int GetNumChannel() const
	{
		return m_nChannels;
	}

	/*!
	* @brief	波形データバンクを取得。
	*/
	WaveFileBank& GetWaveFileBank()
	{
		return m_waveFileBank;
	}

	//インスタンスの生成
	static void SoundEngine::Create()
	{
		if (!m_soundEngine)
		{
			m_soundEngine = new SoundEngine;
		}

	}

	//インスタンスの消去
	static  void SoundEngine::Destroy()
	{
		delete m_soundEngine;
		m_soundEngine = nullptr;
	}
	//インスタンスの取得
	static SoundEngine& GetInstance()
	{
		return *m_soundEngine;
	}
private:
	SoundEngine();
	static SoundEngine* m_soundEngine;
	IXAudio2* m_xAudio2 = nullptr;
	IXAudio2MasteringVoice* m_masteringVoice = nullptr;
	//X3DAUDIO_HANDLE m_hx3DAudio;					//!<3Dオーディオのハンドル。
	IUnknown* m_reverbEffect = nullptr;				//!<リバープエフェクト。
	IXAudio2SubmixVoice* m_submixVoice = nullptr;	//!<サブミックスボイス。
	DWORD m_channelMask = 0;						//!<オーディオチャンネルマスク。
	DWORD m_nChannels = 0;							//!<チャンネル数。
	//float m_fListenerAngle = 0.0f;
	//bool m_UseListenerCone = false;
	//bool m_fUseInnerRadius = false;
	//bool m_useRedirectToLFE = false;
	bool m_isInited = false;
	WaveFileBank m_waveFileBank;					//!<波形データのバンク。
};

//extern SoundEngine* g_soundEngine;