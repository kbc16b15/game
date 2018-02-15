#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager *EnemyManager::m_enemyManager = NULL;

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	//EnemyManager::GetInstance().Release();
}

void EnemyManager::Release()
{
	for (auto TEnemynum : m_tenem)
	{
		if (TEnemynum != nullptr)
		{
			delete TEnemynum;
		}
	}
	//trackingEnemy�̏���
	auto trackingEnemyIt = m_tenem.begin();
	while (trackingEnemyIt != m_tenem.end()) {

		trackingEnemyIt = m_tenem.erase(trackingEnemyIt);
	}

	EnemyManager::GetInstance().Destroy();
}

void EnemyManager::Update()
{
	//�G�̃A�b�v�f�[�g
	for (auto trackingEnemyIt : m_tenem)
	{
		trackingEnemyIt->Update();
	}
}

void EnemyManager::Draw()
{
	//�G�̕`��
	for (auto trackingEnemyIt : m_tenem)
	{
		trackingEnemyIt->Draw();
	}
}