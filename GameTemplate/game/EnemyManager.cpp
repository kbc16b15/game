#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager *EnemyManager::m_enemyManager = NULL;

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	EnemyManager::GetInstance().Release();
}

void EnemyManager::Release()
{
	//trackingEnemyの消去
	auto trackingEnemyIt = m_tenem.begin();
	while (trackingEnemyIt != m_tenem.end()) {

		trackingEnemyIt = m_tenem.erase(trackingEnemyIt);
	}
	for (auto TEnemynum : m_tenem)
	{
		if (TEnemynum != nullptr)
		{
			delete TEnemynum;
			TEnemynum = nullptr;
		}
	}

}

void EnemyManager::Update()
{
	//敵のアップデート
	for (auto trackingEnemyIt : m_tenem)
	{
		trackingEnemyIt->Update();
	}



}

void EnemyManager::Draw()
{
	//敵の描画
	for (auto trackingEnemyIt : m_tenem)
	{
		trackingEnemyIt->Draw();
	}


}