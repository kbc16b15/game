#include "stdafx.h"
#include "Sound.h"


Sound::Sound()
{
}


Sound::~Sound()
{
	//m_masteringVoice->DestroyVoice();
	//if (m_xAudio2)m_xAudio2->Release();
	//CoUninitialize();

	//SourceVoice->DestroyVoice();

}

void Sound::Start(char* name)
{
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);
	//XAudio2Create(&m_xAudio2, 0);
	//m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	//m_Wave.Open(name);

	//m_xAudio2->CreateSourceVoice(&SourceVoice, m_pwfx);


	////buffer.AudioBytes = dwChunkSize;
	////buffer.pAudioData = pDataBuffer;
	//buffer.Flags = XAUDIO2_END_OF_STREAM;
	//buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	//SourceVoice->SubmitSourceBuffer(&buffer);


}

void Sound::Update()
{
	//IXAudio2SourceVoice* voice;
	//m_xAudio2->StartEngine();
}