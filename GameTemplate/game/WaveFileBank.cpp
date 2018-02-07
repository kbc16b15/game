#include "stdafx.h"
#include "WaveFileBank.h"
#include "WaveFile.h"
#include "Util.h"

WaveFileBank::WaveFileBank()
{
}


WaveFileBank::~WaveFileBank()
{
	ReleaseAll();
}

void WaveFileBank::Release(int groupID)
{
	for (auto waveFile : m_waveFileMap[groupID]) {
		waveFile.second->Release();
	}
	m_waveFileMap[groupID].clear();
}
void WaveFileBank::RegistWaveFile(int groupID, CWaveFilePtr waveFile)
{
	//TK_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
	m_waveFileMap[groupID].insert({ waveFile->GetFilePathHash(), waveFile });
}
CWaveFilePtr WaveFileBank::FindWaveFile(int groupID, const char* filePath)
{
	//TK_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
	auto value = m_waveFileMap[groupID].find(CUtil::MakeHash(filePath));
	if (value != m_waveFileMap[groupID].end()) {
		return value->second;
	}
	return CWaveFilePtr();
}
//CWaveFilePtr WaveFileBank::FindWaveFile(int groupID, const NameKey& nameKey)
//{
//	//TK_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
//	auto value = m_waveFileMap[groupID].find(nameKey.GetHashCode());
//	if (value != m_waveFileMap[groupID].end()) {
//		return value->second;
//	}
//	return CWaveFilePtr();
//}