#include "stdafx.h"
#include "SoundEngine.h"
#include "Sound.h"

//extern SoundEngine* g_soundEngine;

Sound::Sound()
{
	memset(m_emitterAzimuths, 0, sizeof(m_emitterAzimuths));
	memset(m_matrixCoefficients, 0, sizeof(m_matrixCoefficients));
}


Sound::~Sound()
{
	Release();
}

void Sound::Release()
{
	if (SourceVoice != nullptr) {
		SourceVoice->DestroyVoice();
		SourceVoice = nullptr;
	}

}

void Sound::Init(char* filePath, bool is3DSound)
{
	m_waveFile = SoundEngine::GetInstance().GetWaveFileBank().FindWaveFile(0, filePath);
	
	if (!m_waveFile) {
		m_waveFile.reset(new WaveFile);
		m_waveFile->Open(filePath);
		SoundEngine::GetInstance().GetWaveFileBank().RegistWaveFile(0, m_waveFile);
		m_waveFile->AllocReadBuffer(m_waveFile->GetSize());//waveファイルのサイズ分の読み込みバッファを確保する。
		SoundEngine::GetInstance().GetWaveFileBank().RegistWaveFile(0,m_waveFile);
		unsigned int dummy;
		m_waveFile->Read(m_waveFile->GetReadBuffer(), m_waveFile->GetSize(), &dummy);
		m_waveFile->ResetFile();

	}

	//サウンドボイスソースを作成。
	
	SourceVoice = SoundEngine::GetInstance().CreateXAudio2SourceVoice(m_waveFile.get(),false);
}

//void Sound::Init(const NameKey& nameKey,bool is3DSound)
//{
//	m_waveFile = g_soundEngine->GetWaveFileBank().FindWaveFile(0, nameKey);
//
//	if (!m_waveFile) {
//		m_waveFile.reset(new WaveFile);
//		m_waveFile->Open(nameKey.GetName());
//		g_soundEngine->GetWaveFileBank().RegistWaveFile(0, m_waveFile);
//		m_waveFile->AllocReadBuffer(m_waveFile->GetSize());//waveファイルのサイズ分の読み込みバッファを確保する。
//		g_soundEngine->GetWaveFileBank().RegistWaveFile(0, m_waveFile);
//		unsigned int dummy;
//		m_waveFile->Read(m_waveFile->GetReadBuffer(), m_waveFile->GetSize(), &dummy);
//		m_waveFile->ResetFile();
//
//	}
//
//	//サウンドボイスソースを作成。
//
//	SourceVoice = g_soundEngine->CreateXAudio2SourceVoice(m_waveFile.get(), is3DSound);
//}

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
			Release();
			//delete this;
		}
	}
}
void Sound::Update()
{
	UpdateOnMemory();
	
}