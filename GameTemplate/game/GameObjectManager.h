#pragma once
#include "IGameObject.h"

class GameObjectManager
{
public:
	~GameObjectManager();
	//template<class T>
	void AddGameObject(IGameObject* go);
	void DeleteGameObject(IGameObject* go);

	void Init();
	void Update();
	void Draw();

	//インスタンスの生成
	static  void GameObjectManager::Create()
	{
		if (!m_goMgr)
		{
			m_goMgr = new GameObjectManager;
		}
	}

	//インスタンスの消去
	static  void GameObjectManager::Destroy()
	{
		delete m_goMgr;
		m_goMgr = nullptr;
	}
	//インスタンスの取得
	static GameObjectManager& GetGameObjectManager()
	{
		return *m_goMgr;
	}
	

private:
	GameObjectManager();
	static GameObjectManager* m_goMgr;
	std::list<IGameObject*>		m_gameObjects;
};

