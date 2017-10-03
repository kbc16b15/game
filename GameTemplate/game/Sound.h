#pragma once
#include "WaveFile.h"
class Sound
{
public:
	Sound();
	~Sound();
	void Start();
	void Update();
private:
	IXAudio2SourceVoice*	SourceVoice = NULL;
	IXAudio2*				m_xAudio2 = nullptr;
	IXAudio2MasteringVoice* m_masteringVoice = nullptr;
	XAUDIO2_VOICE_STATE		xa2state;
	WAVEFORMATEX*			m_pwfx=nullptr;
	XAUDIO2_BUFFER			buffer;
	WaveFile				m_Wave;

};

