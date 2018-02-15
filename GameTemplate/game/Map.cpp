#include "stdafx.h"
#include "Map.h"
#include "MapObject.h"
//#include "MoveObject.h"
//#include "TrapObject.h"
//#include "FallObject.h"
//#include "GoalObject.h"
//#include "MapChip.h"
//#include "Spring.h"
//#include "BoxChip.h"
//#include "RotObject.h"
//#include "GravityObject.h"
//#include "MoveCube.h"
//#include "Sea.h"
//#include "Sky.h"
#include "HealItem.h"
#include "BossEnemy.h"
#include "Player.h"
#include "MapManager.h"
#include "EnemyManager.h"
#include "BossHp.h"
#include "GameObjectManager.h"
#include "BulletWeapon.h"
#include "BulletManager.h"

Map *Map::m_map = NULL;

SMapChipLocInfo Info1[] = {
#include "locationinfo7.h"
};

SMapChipLocInfo Info2[] = {

#include "locationinfo8.h"
};

Map::Map()
{
	MapManager::Create();
}

Map::~Map()
{
	MapManager::GetMapManager().Release();
}

void Map::Init(/*SMapChipLocInfo Info[]*/)
{
	
	//SMapChipLocInfo Info[255];
	//int numObject/*=sizeof(Info1) / sizeof(Info1[0]);*/;
	//for (int i = 0; i < numObject; i++)
	//{
	//	Info[i] = Info1[i];
	//}

	switch (m_stageNum)
	{
	case STAGE::STAGE1://�X�e�[�W�P
		MapLoad1();
		break;
	case STAGE::STAGE2://�X�e�[�W�Q
		MapLoad2();
		break;
	default:
		break;
	}
	
	
}

void Map::Update()
{
	//�}�b�v�`�b�v������X�V�B
	MapManager::GetMapManager().Update();

	for (int i = 0; i < m_healList.size(); i++)
	{
		m_healList[i]->Update();
	}

	//�񕜃A�C�e�����擾���������
	auto HealIt = m_healList.begin();
	while (HealIt != m_healList.end()) {
		if ((*HealIt)->GetHeal()) {
			HealIt = m_healList.erase(HealIt);
		}
		else {
			HealIt++;
		}
	}
}

void Map::Draw()
{
	//�}�b�v�`�b�v������`��
	MapManager::GetMapManager().Draw();

	for (int i = 0; i < m_healList.size(); i++)
	{
		m_healList[i]->Draw();
	}

}

void Map::MapCreate(const char* mapName,int no,SMapChipLocInfo info[])
{
	MapObject* mapOb=nullptr;
	mapOb =mapOb->MapReturn(mapName);
	mapOb->Init(info[no].modelName, info[no].pos, info[no].rot);
	MapManager::GetMapManager().AddMap(mapOb);
}

void Map::MapLoad1()
{
	int numObject = sizeof(Info1) / sizeof(Info1[0]);

	for (int i = 0; i < numObject; i++) {

		if (strcmp(Info1[i].modelName, "dore") == 0)
		{
			//MapObject* ob; 
			//ob = new MoveObject();
			////MoveObject* moveChip = new MoveObject;
			//ob->Init(Info1[i].modelName, Info1[i].pos, Info1[i].rotation);
			//MapManager::GetMapManager().AddMap(ob);
			MapCreate("MoveObject", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "BCube") == 0)
		{
			MapCreate("BoxChip", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "BCube2") == 0)
		{
			MapCreate("BoxChip", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "TCircle") == 0)//��]�@�_���[�W�I�u�W�F�N�g
		{
			MapCreate("TCircle", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "FCubeF") == 0)
		{
			MapCreate("FCubeF", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "FCubeB") == 0)
		{
			MapCreate("FCubeB", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "FCubeR") == 0)
		{
			MapCreate("FCubeR", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "FCubeL") == 0)
		{
			MapCreate("FCubeL", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "GoalCube") == 0)//�S�[���n�_
		{
			MapCreate("GoalObject", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "HealItem") == 0)//�񕜃A�C�e��
		{
			HealItem* healChip = new HealItem;
			healChip->Init(Info1[i].modelName, Info1[i].pos, Info1[i].rot);
			m_healList.push_back(healChip);
		}
		else if (strcmp(Info1[i].modelName, "Boss") == 0)
		{
			BossEnemy::Create();
			BossHp::Create();
			BossEnemy::GetInstance().Init(Info1[i].pos, Info1[i].rot);
			BossHp::GetInstance().Init();

			GameObjectManager::GetGameObjectManager().AddGameObject(&BossEnemy::GetInstance());
			GameObjectManager::GetGameObjectManager().AddGameObject(&BossHp::GetInstance());

		}
		else if (strcmp(Info1[i].modelName, "Drone") == 0)//�G�l�~�[�̈ʒu�ݒ�
		{
			/*BulletWeapon* weapon = new BulletWeapon;
			BulletManager::GetInstance().AddBulletWeapon(weapon);*/
			trackingEnemy* Tenemy = new trackingEnemy;
			EnemyManager::GetInstance().AddTrackingEnemy(Tenemy);
			Tenemy->Init(Info1[i].pos, Info1[i].rot);
		}
		else if (strcmp(Info1[i].modelName, "unity") == 0)//�v���C���[�̏����ʒu
		{
			Player::GetInstance().Setpos(Info1[i].pos);
		}
		else {
			//�I�u�W�F�N�g��������[�h���Ă����B
			//MapChip�̃C���X�^���X�𓮓I�ɐ����B
			//MapChip* mapChip = new MapChip;
			////�}�b�v�`�b�v�̏���n���ď������B
			//mapChip->Init(Info1[i].modelName, Info1[i].pos, Info1[i].rotation);
			//���I�z��Ƀv�b�V���B
			MapCreate("map", i, &Info1[0]);
		}

	}
}


void Map::MapLoad2()
{
	int numObject = sizeof(Info2) / sizeof(Info2[0]);

	for (int i = 0; i < numObject; i++) {

		if (strcmp(Info2[i].modelName, "dore") == 0)
		{
			MapCreate("MoveObject", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "BCube") == 0)
		{
			MapCreate("BoxChip", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "BCube2") == 0)
		{
			MapCreate("BoxChip", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "TCircle") == 0)//��]�@�_���[�W�I�u�W�F�N�g
		{
			MapCreate("TCircle", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "FCubeF") == 0)
		{
			MapCreate("FCubeF", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "FCubeB") == 0)
		{
			MapCreate("FCubeB", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "FCubeR") == 0)
		{
			MapCreate("FCubeR", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "FCubeL") == 0)
		{
			MapCreate("FCubeL", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "GoalCube") == 0)//�S�[���n�_
		{
			MapCreate("GoalObject", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "HealItem") == 0)//�񕜃A�C�e��
		{
			HealItem* healChip = new HealItem;
			healChip->Init(Info2[i].modelName, Info2[i].pos, Info2[i].rot);
			m_healList.push_back(healChip);
		}
		else if (strcmp(Info2[i].modelName, "Boss") == 0)
		{
			BossEnemy::Create();
			BossHp::Create();
			BossEnemy::GetInstance().Init(Info2[i].pos, Info2[i].rot);
			BossHp::GetInstance().Init();

			GameObjectManager::GetGameObjectManager().AddGameObject(&BossEnemy::GetInstance());
			GameObjectManager::GetGameObjectManager().AddGameObject(&BossHp::GetInstance());

		}
		else if (strcmp(Info2[i].modelName, "Drone") == 0)//�G�l�~�[�̈ʒu�ݒ�
		{
			trackingEnemy* Tenemy = new trackingEnemy;
			EnemyManager::GetInstance().AddTrackingEnemy(Tenemy);
			Tenemy->Init(Info2[i].pos, Info2[i].rot);
		}
		else if (strcmp(Info2[i].modelName, "unity") == 0)//�v���C���[�̏����ʒu
		{
			Player::GetInstance().Setpos(Info2[i].pos);
		}
		else {
			MapCreate("map", i, &Info2[0]);
		}

	}
}