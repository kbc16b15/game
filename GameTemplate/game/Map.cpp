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
//#include "MapInfo.h"

Map *Map::m_map = NULL;
SMapChipLocInfo Info1[] = {
#include "locationinfo7.h"
};

SMapChipLocInfo Info2[] = {

#include "locationinfo7.h"
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
	
	SMapChipLocInfo Info[255];
	int numObject = sizeof(Info1) / sizeof(Info1[0]);
	for (int i = 0; i < numObject; i++)
	{
		Info[i] = Info1[i];
	}

	switch (m_stageNum)
	{
	case STAGE1://�X�e�[�W�P
		numObject = sizeof(Info1) / sizeof(Info1[0]);
		for (int i = 0; i < numObject; i++)
		{
			Info[i] = Info1[i];
		}
		break;
	case STAGE2://�X�e�[�W�Q
		numObject = sizeof(Info2) / sizeof(Info2[0]);
		for (int i = 0; i < numObject; i++)
		{
			Info[i] = Info2[i];
		}
		break;
	default:
		break;
	}
	
	for (int i = 0; i < numObject; i++) {
		
		if (strcmp(Info[i].modelName, "dore") == 0)
		{
			//MapObject* ob; 
			//ob = new MoveObject();
			////MoveObject* moveChip = new MoveObject;
			//ob->Init(Info[i].modelName, Info[i].pos, Info[i].rotation);
			//MapManager::GetMapManager().AddMap(ob);
			MapCreate("MoveObject", i, &Info[0]);
		}
		else if (strcmp(Info[i].modelName, "BCube") == 0)
		{
			MapCreate("BoxChip", i, &Info[0]);
		}
		else if (strcmp(Info[i].modelName, "BCube2") == 0)
		{
			MapCreate("BoxChip", i, &Info[0]);
		}
		else if (strcmp(Info[i].modelName, "TCircle") == 0)//��]�@�_���[�W�I�u�W�F�N�g
		{
			MapCreate("TCircle", i, &Info[0]);
		}
		else if (strcmp(Info[i].modelName, "FCubeF") == 0)
		{
			MapCreate("FCubeF", i, &Info[0]);
		}
		else if (strcmp(Info[i].modelName, "FCubeB") == 0)
		{
			MapCreate("FCubeB", i, &Info[0]);
		}
		else if (strcmp(Info[i].modelName, "FCubeR") == 0)
		{
			MapCreate("FCubeR", i, &Info[0]);
		}
		else if (strcmp(Info[i].modelName, "FCubeL") == 0)
		{
			MapCreate("FCubeL", i, &Info[0]);
		}
		else if (strcmp(Info[i].modelName, "GoalCube") == 0)//�S�[���n�_
		{
			MapCreate("GoalObject", i, &Info[0]);
		}
		else if (strcmp(Info[i].modelName, "HealItem") == 0)//�񕜃A�C�e��
		{
			HealItem* healChip = new HealItem;
			healChip->Init(Info[i].modelName, Info[i].pos, Info[i].rot);
			m_healList.push_back(healChip);
		}
		else if (strcmp(Info[i].modelName, "Boss") == 0)
		{
			BossEnemy::Create();
			BossHp::Create();
			BossEnemy::GetInstance().Init(Info[i].pos, Info[i].rot);
			BossHp::GetInstance().Init();

			GameObjectManager::GetGameObjectManager().AddGameObject(&BossEnemy::GetInstance());
			GameObjectManager::GetGameObjectManager().AddGameObject(&BossHp::GetInstance());

		}
		else if (strcmp(Info[i].modelName, "Drone") == 0)//�G�l�~�[�̈ʒu�ݒ�
		{
			BulletWeapon* weapon = new BulletWeapon;
			BulletManager::GetInstance().AddBulletWeapon(weapon);
			/*trackingEnemy* Tenemy = new trackingEnemy;
			EnemyManager::GetInstance().AddTrackingEnemy(Tenemy);*/
			weapon->Init(Info[i].pos, Info[i].rot);
		}
		else if (strcmp(Info[i].modelName, "unity") == 0)//�v���C���[�̏����ʒu
		{
			Player::GetInstance().Setpos(Info[i].pos);
		}
		else {
			//�I�u�W�F�N�g��������[�h���Ă����B
			//MapChip�̃C���X�^���X�𓮓I�ɐ����B
			//MapChip* mapChip = new MapChip;
			////�}�b�v�`�b�v�̏���n���ď������B
			//mapChip->Init(Info[i].modelName, Info[i].pos, Info[i].rotation);
			//���I�z��Ƀv�b�V���B
			MapCreate("map", i, &Info[0]);
		}

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