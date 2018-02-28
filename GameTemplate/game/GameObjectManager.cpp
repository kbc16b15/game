#include "stdafx.h"
#include "GameObjectManager.h"
//#include "game.h"

GameObjectManager *GameObjectManager::m_goMgr = NULL;

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}


void GameObjectManager::AddGameObject(IGameObject* go)
{
	m_gameObjects.push_back(go);
}

void GameObjectManager::DeleteGameObject(IGameObject* go)
{
	//auto gameObjectsIt = m_gameObjects.begin();
	//while (gameObjectsIt != m_gameObjects.end()) {
	//	if ((*gameObjectsIt)==go/*(*gameObjectsIt)->GetDeathflg()*/) {
	//		gameObjectsIt = m_gameObjects.erase(gameObjectsIt);
	//	}
	//	else {
	//		gameObjectsIt++;
	//	}
	//}

	//std::list<IGameObject*> it;
	//for (it = m_gameObjects.begin(); it != m_gameObjects.end(); ) {  // <-「it++」を削除
	//	if ((*it) == go) {
	//		it = m_gameObjects.erase(it);
	//		continue;
	//	}
	//	it++;  // ここで次のイテレートに
	//}

	m_gameObjects.erase(
		std::remove(m_gameObjects.begin(), m_gameObjects.end(), go),
		m_gameObjects.end()
	);

}

void GameObjectManager::Init()
{
	
	for (IGameObject* go : m_gameObjects) {
		if (go->GetActive())
		{
			go->Init();
		}
	}
}

void GameObjectManager::Update()
{
	for (IGameObject* gu : m_gameObjects) {
		if (gu->GetActive())
		{
			gu->Update();
		}
	}


}

void GameObjectManager::Draw()
{
	for (IGameObject* gl : m_gameObjects)
	{
		if (gl->GetActive())
		{
			gl->Draw();
		}
	}

	for (IGameObject* ghd : m_gameObjects)
	{
		if (ghd->GetActive())
		{
			ghd->HudDraw();
		}
	}

	for (IGameObject* gppd : m_gameObjects)
	{
		if (gppd->GetActive())
		{
			gppd->PrePostDraw();
		}
	}

	for (IGameObject* gpd : m_gameObjects)
	{
		if (gpd->GetActive())
		{
			gpd->PostDraw();
		}
	}
}

//IGameObject* IGameObject::ObjectFactory(const char* ObjectName)
//{
//	/*IGameObject* ob = nullptr;
//	if (strcmp("Player", ObjectName) == 0) {
//		m_player = new Player();
//		ob = m_player;
//	}
//
//
//	return ob;*/
//}

