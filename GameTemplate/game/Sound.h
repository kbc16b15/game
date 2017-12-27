#pragma once
#include "WaveFile.h"
#include "SoundEngine.h"
#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//�ő�o�̓`�����l�����B
class Sound
{
public:
	Sound();
	~Sound();
	//void Start(char* name);
	void Update();

	void Init(char* filePath, bool is3DSound = false);

	void Play(bool isLoop);
	/*!
	* @brief	��~�B
	*/
	void Stop()
	{
		SourceVoice->Stop();
		m_isPlaying = false;
	}
	/*!
	* @brief	�ꎞ��~�B
	*/
	void Pause()
	{
		SourceVoice->Stop(/*XAUDIO2_PLAY_TAILS*/);
	}
	/*!
	* @brief	�Đ����H�B
	*/
	bool IsPlaying() const
	{
		return m_isPlaying;
	}
	/*!
	* @brief	�X�V�B
	*@param[in]	isLoop		���[�v�Đ��t���O�B
	*/
	/*!
	* @brief	�{�����[����ݒ�B
	*@param[in]	vol		�{�����[���B
	*/
	void SetVolume(float vol)
	{
		SourceVoice->SetVolume(vol);
	}
	/*!
	* @brief	���[�v�t���O���擾�B
	*/
	bool GetLoopFlag() const
	{
		return m_isLoop;
	}
	/*!
	* @brief	�{�C�X�̎��g��������
	*@details
	* �ڍׂ�IXAudio2SourceVoice��SetFrequencyRatio���Q�Ƃ��Ă��������B
	*@param[in]	ratio		���g����B
	*/
	void SetFrequencyRatio(float ratio)
	{
		if (SourceVoice != nullptr) {
			SourceVoice->SetFrequencyRatio(ratio);
		}
	}
	//���̓`�����l�������擾�B
	int GetNumInputChannel()const
	{
		return m_waveFile->GetFormat()->nChannels;
	}
	FLOAT32* GetEmitterAzimuths()
	{
		return m_emitterAzimuths;
	}
	FLOAT32* GetMatrixCoefficients()
	{
		return m_matrixCoefficients;
	}

	IXAudio2SourceVoice* GetXAudio2SourceVoice()
	{
		return SourceVoice;
	}

	void Release();

	//�I���������Đ����̍X�V�����B
	void UpdateOnMemory();
private:
	void Play(char* buff, unsigned int bufferSize);
private:
	SoundEngine* SE;
	//IXAudio2*				m_xAudio2 = nullptr;
	//IXAudio2MasteringVoice* m_masteringVoice = nullptr;
	//XAUDIO2_VOICE_STATE		xa2state;
	//WAVEFORMATEX*			m_pwfx=nullptr;
	//XAUDIO2_BUFFER			buffer;
	//WaveFile				m_Wave;
	IXAudio2SourceVoice*	SourceVoice = nullptr;
	std::shared_ptr<WaveFile>	m_waveFile;					//!<�g�`�f�[�^
	bool						m_isLoop = false;			//!<���[�v�t���O�B
	bool						m_isPlaying = false;		//!<�Đ����t���O�B
	unsigned int			m_readStartPos = 0;			//!<�ǂݍ��݊J�n�ʒu�B

	FLOAT32 m_emitterAzimuths[INPUTCHANNELS];
	FLOAT32 m_matrixCoefficients[INPUTCHANNELS * OUTPUTCHANNELS];
	X3DAUDIO_DSP_SETTINGS m_dspSettings;


};

