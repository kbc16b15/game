#include "stdafx.h"
#include "MapManager.h"

MapManager *MapManager::m_mapManager = NULL;

MapManager::MapManager()
{
}


MapManager::~MapManager()
{

	/*for (auto mapnum : m_mapList)
	{
		delete mapnum;
	}
	auto mapIt = m_mapList.begin();
	while (mapIt != m_mapList.end())
	{
		mapIt = m_mapList.erase(mapIt);
	}*/
	//Release();
}

void MapManager::Release()
{
	/*auto mapIt = m_mapList.begin();
	while (m_mapList.size() > 0)
	{
		MapObject* temp = m_mapList.erase();
		delete temp;
	}*/

	for (auto mapnum : m_mapList)
	{
		delete mapnum;
	}
	auto mapIt = m_mapList.begin();
	while (mapIt != m_mapList.end())
	{
		mapIt = m_mapList.erase(mapIt);
	
	}
	//m_mapList.clear();
	MapManager::GetMapManager().Destroy();
}

void MapManager::AddMap(MapObject* go)
{
	m_mapList.push_back(go);
}

void MapManager::DeleteMap(MapObject* go)
{

	m_mapList.erase(
		std::remove(m_mapList.begin(), m_mapList.end(), go),
		m_mapList.end()
	);

}

void MapManager::Update()
{
	for (MapObject* gu : m_mapList) {

		gu->Update();
	}
}

void MapManager::Draw()
{
	for (MapObject* gl : m_mapList)
	{
		gl->Draw();
	}
}