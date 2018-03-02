#pragma once
#include "IGameObject.h"
class GameObjectManager
{
public:
	~GameObjectManager();

	void AddGameObject(IGameObject* go);
	void DeleteGameObject(IGameObject* go);
	/*IGameObject* FindGameObject(const char* Name);
	IGameObject* GameObjectManager::FindGameObject(const char* Name){
		for (IGameObject* gd : m_gameObjects)
		{
			if (strcmp(gd->GetName(), Name) == 0)
			{
				return gd->GetInstance();
			}
		}
	}*/
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

