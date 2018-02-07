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
}

void MapManager::Release()
{
	for (auto mapnum : m_mapList)
	{
		delete mapnum;
	}
	auto mapIt = m_mapList.begin();
	while (mapIt != m_mapList.end())
	{
		mapIt = m_mapList.erase(mapIt);
	}
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