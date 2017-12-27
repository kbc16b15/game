#include "stdafx.h"
#include "SoundEngine.h"
#include "Sound.h"


Sound::Sound()
{
	memset(m_emitterAzimuths, 0, sizeof(m_emitterAzimuths));
	memset(m_matrixCoefficients, 0, sizeof(m_matrixCoefficients));
}


Sound::~Sound()
{
	Release();
	delete SE;
}

void Sound::Release()
{

	if (SourceVoice != nullptr) {
		SourceVoice->DestroyVoice();
		SourceVoice = nullptr;
	}
}
//void Sound::Start(char* name)
//{
//
//	CoInitializeEx(NULL, COINIT_MULTITHREADED);
//XAudio2Create(&m_xAudio2, 0);
//
//
//m_xAudio2->CreateSourceVoice(&SourceVoice, m_pwfx);
//
//	////buffer.AudioBytes = dwChunkSize;
//	////buffer.pAudioData = pDataBuffer;
//	//buffer.Flags = XAUDIO2_END_OF_STREAM;
//	//buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
//
//	//SourceVoice->SubmitSourceBuffer(&buffer);
//
//
//}
//
//void Sound::Update()
//{
//	//IXAudio2SourceVoice* voice;
//	//m_xAudio2->StartEngine();
//}

void Sound::Init(char* filePath, bool is3DSound)
{
	SE = new SoundEngine;
	//m_waveFile = SoundEngine().GetWaveFileBank().FindWaveFile(0, filePath);
	if (!m_waveFile) {
		m_waveFile.reset(new WaveFile);
		m_waveFile->Open(filePath);
		m_waveFile->AllocReadBuffer(m_waveFile->GetSize());//waveファイルのサイズ分の読み込みバッファを確保する。
		unsigned int dummy;
		m_waveFile->Read(m_waveFile->GetReadBuffer(), m_waveFile->GetSize(), &dummy);
		m_waveFile->ResetFile();

	}

	//サウンドボイスソースを作成。
	
	SourceVoice = SE->CreateXAudio2SourceVoice(m_waveFile.get(), is3DSound);
}

void Sound::Play(char* buff, unsigned int bufferSize)
{
	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = (BYTE*)buff;
	buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
	buffer.AudioBytes = bufferSize;
	if (SourceVoice != nullptr && bufferSize > 0) {
		//再生開始。
		if (FAILED(SourceVoice->SubmitSourceBuffer(&buffer))) {
			Release();
			return;
		}
	}
}
void Sound::Play(bool isLoop)
{
	if (m_isPlaying) {
		//再生中のものを再開する。
		SourceVoice->Start(0);
	}
	else
	{
		SourceVoice->FlushSourceBuffers();
		SourceVoice->Start(0);
		Play(m_waveFile->GetReadBuffer(), m_waveFile->GetSize());

		m_isPlaying = true;
	}
	m_isLoop = isLoop;
}

void Sound::UpdateOnMemory()
{
	if (!m_isPlaying) {
		return;
	}
	XAUDIO2_VOICE_STATE state;
	SourceVoice->GetState(&state);
	if (state.BuffersQueued <= 0) {
		m_isPlaying = false;
		if (m_isLoop)
		{
			//ループ。
			Play(m_isLoop);
		}
		else {
			delete this;
		}
	}
}
void Sound::Update()
{
	UpdateOnMemory();
	
}