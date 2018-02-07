#pragma once
#include "MapObject.h"
class MapManager
{
public:
	//MapManager();
	~MapManager();

	//マップの読み込み
	void AddMap(MapObject* go);
	//マップの消去
	void DeleteMap(MapObject* go);
	//更新
	void Update();
	//描画
	void Draw();
	//開放
	void Release();
	//インスタンスの生成
	static  void MapManager::Create()
	{
		if (!m_mapManager)
		{
			m_mapManager = new MapManager;
		}
	}

	//インスタンスの消去
	static  void MapManager::Destroy()
	{
		delete m_mapManager;
		m_mapManager = nullptr;
	}
	//インスタンスの取得
	static MapManager& GetMapManager()
	{
		return *m_mapManager;
	}


private:
	MapManager();
	std::list<MapObject*> m_mapList;		//基底クラスのリスト
	static MapManager* m_mapManager;
};

