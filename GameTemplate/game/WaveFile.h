#pragma once
#include <thread>
class WaveFile
{
public:
	WaveFile();
	~WaveFile();

	void Open(const char* fileName);
	void Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead);
	void Release();

	DWORD GetSize()
	{
		return m_dwSize;
	}

	WAVEFORMATEX* GetFormat()
	{
		return m_pwfx;
	}
	bool ReadEnd()
	{
		return isReadEnd;
	}
private:
	HMMIO			m_hmmio = nullptr;
	bool			isReadEnd = true;
	WAVEFORMATEX*	m_pwfx=nullptr;
	DWORD			m_dwSize = 0;
	std::string		m_filePath;
};

