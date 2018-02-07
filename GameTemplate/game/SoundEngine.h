#pragma once
#include "WaveFileBank.h"
#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//�ő�o�̓`�����l�����B
class SoundEngine
{
public:
	~SoundEngine();

	//class CWaveFile;
	//class CSoundSource;
	/*!
	* @brief	�������B
	*/
	void Init();
	/*!
	* @brief	�J���B
	*/
	void Release();
	/*!
	* @brief	�X�V�B
	*/
	void Update();
	
	/*!
	* @brief	XAudio2�̃\�[�X�{�C�X���쐬�B
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
	* @brief	�o�̓`�����l���̐����擾�B
	*/
	int GetNumChannel() const
	{
		return m_nChannels;
	}

	/*!
	* @brief	�g�`�f�[�^�o���N���擾�B
	*/
	WaveFileBank& GetWaveFileBank()
	{
		return m_waveFileBank;
	}

	//�C���X�^���X�̐���
	static void SoundEngine::Create()
	{
		if (!m_soundEngine)
		{
			m_soundEngine = new SoundEngine;
		}

	}

	//�C���X�^���X�̏���
	static  void SoundEngine::Destroy()
	{
		delete m_soundEngine;
		m_soundEngine = nullptr;
	}
	//�C���X�^���X�̎擾
	static SoundEngine& GetInstance()
	{
		return *m_soundEngine;
	}
private:
	SoundEngine();
	static SoundEngine* m_soundEngine;
	IXAudio2* m_xAudio2 = nullptr;
	IXAudio2MasteringVoice* m_masteringVoice = nullptr;
	//X3DAUDIO_HANDLE m_hx3DAudio;					//!<3D�I�[�f�B�I�̃n���h���B
	IUnknown* m_reverbEffect = nullptr;				//!<���o�[�v�G�t�F�N�g�B
	IXAudio2SubmixVoice* m_submixVoice = nullptr;	//!<�T�u�~�b�N�X�{�C�X�B
	DWORD m_channelMask = 0;						//!<�I�[�f�B�I�`�����l���}�X�N�B
	DWORD m_nChannels = 0;							//!<�`�����l�����B
	//float m_fListenerAngle = 0.0f;
	//bool m_UseListenerCone = false;
	//bool m_fUseInnerRadius = false;
	//bool m_useRedirectToLFE = false;
	bool m_isInited = false;
	WaveFileBank m_waveFileBank;					//!<�g�`�f�[�^�̃o���N�B
};

//extern SoundEngine* g_soundEngine;