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

	//�C���X�^���X�̐���
	static  void GameObjectManager::Create()
	{
		if (!m_goMgr)
		{
			m_goMgr = new GameObjectManager;
		}
	}

	//�C���X�^���X�̏���
	static  void GameObjectManager::Destroy()
	{
		delete m_goMgr;
		m_goMgr = nullptr;
	}
	//�C���X�^���X�̎擾
	static GameObjectManager& GetGameObjectManager()
	{
		return *m_goMgr;
	}
	

private:
	GameObjectManager();
	static GameObjectManager* m_goMgr;
	std::list<IGameObject*>		m_gameObjects;
};

