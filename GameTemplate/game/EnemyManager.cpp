#include "stdafx.h"
#include "EnemyManager.h"

//EnemyManager *EnemyManager::m_enemyManager = NULL;

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	Release();
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
	//delete this;
	//SceneManager::GetGame().GetEnemyManager.Destroy();
}

void EnemyManager::Update()
{
	//�G�̃A�b�v�f�[�g
	for (auto trackingEnemyIt : m_tenem)
	{
		if (trackingEnemyIt->GetActive())
		{
			trackingEnemyIt->Update();
		}
	}

	for (auto Enemynum : m_tenem)
	{
		if (Enemynum->GetDeathflg())
		{
			/*delete */Enemynum->SetActive(false);
		}
	}
	//trackingEnemy�̏���
	/*auto EnemyIt = m_tenem.begin();
	while (EnemyIt != m_tenem.end()) {
		if ((*EnemyIt)->GetDeathflg())
		{
			EnemyIt = m_tenem.erase(EnemyIt);
		}
		else
		{
			EnemyIt++;
		}
	}*/
}

void EnemyManager::Draw()
{
	//�G�̕`��
	for (auto trackingEnemyIt : m_tenem)
	{
		if (trackingEnemyIt->GetActive())
		{
			trackingEnemyIt->Draw();
		}
	}
}