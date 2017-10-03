#include "stdafx.h"
#include "WaveFile.h"



WaveFile::WaveFile()
{
}


WaveFile::~WaveFile()
{
}

void WaveFile::Open(const char* fileName)
{
	m_filePath = fileName;
	m_hmmio = mmioOpen(const_cast<char*>(fileName), NULL, MMIO_ALLOCBUF | MMIO_READ);
	isReadEnd = true;
}

void WaveFile::Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead)
{
	

}
