#include "stdafx.h"
#include "GameObjectManager.h"

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

		go->Init();
		
	}
}

void GameObjectManager::Update()
{
	for (IGameObject* gu : m_gameObjects) {
		
		gu->Update();
	}
}

void GameObjectManager::Draw()
{
	for (IGameObject* gl : m_gameObjects)
	{
		gl->Draw();
	}
}