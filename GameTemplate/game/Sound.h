#pragma once
#include "WaveFile.h"
#include "SoundEngine.h"
#define INPUTCHANNELS 2  // number of source channels
#define OUTPUTCHANNELS 8	//最大出力チャンネル数。
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
	* @brief	停止。
	*/
	void Stop()
	{
		SourceVoice->Stop();
		m_isPlaying = false;
	}
	/*!
	* @brief	一時停止。
	*/
	void Pause()
	{
		SourceVoice->Stop(/*XAUDIO2_PLAY_TAILS*/);
	}
	/*!
	* @brief	再生中？。
	*/
	bool IsPlaying() const
	{
		return m_isPlaying;
	}
	/*!
	* @brief	更新。
	*@param[in]	isLoop		ループ再生フラグ。
	*/
	/*!
	* @brief	ボリュームを設定。
	*@param[in]	vol		ボリューム。
	*/
	void SetVolume(float vol)
	{
		SourceVoice->SetVolume(vol);
	}
	/*!
	* @brief	ループフラグを取得。
	*/
	bool GetLoopFlag() const
	{
		return m_isLoop;
	}
	/*!
	* @brief	ボイスの周波数調整比
	*@details
	* 詳細はIXAudio2SourceVoiceのSetFrequencyRatioを参照してください。
	*@param[in]	ratio		周波数比。
	*/
	void SetFrequencyRatio(float ratio)
	{
		if (SourceVoice != nullptr) {
			SourceVoice->SetFrequencyRatio(ratio);
		}
	}
	//入力チャンネル数を取得。
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

	//オンメモリ再生中の更新処理。
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
	std::shared_ptr<WaveFile>	m_waveFile;					//!<波形データ
	bool						m_isLoop = false;			//!<ループフラグ。
	bool						m_isPlaying = false;		//!<再生中フラグ。
	unsigned int			m_readStartPos = 0;			//!<読み込み開始位置。

	FLOAT32 m_emitterAzimuths[INPUTCHANNELS];
	FLOAT32 m_matrixCoefficients[INPUTCHANNELS * OUTPUTCHANNELS];
	X3DAUDIO_DSP_SETTINGS m_dspSettings;


};

