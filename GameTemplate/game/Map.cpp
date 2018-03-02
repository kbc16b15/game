#include "stdafx.h"
#include "Map.h"
#include "MapObject.h"
#include "HealItem.h"
#include "BossEnemy.h"
#include "BossHp.h"
#include "Player.h"
#include "MapManager.h"
#include "EnemyManager.h"
//#include "SceneChange.h"
#include "GameObjectManager.h"
//#include "BulletWeapon.h"
//#include "BulletManager.h"
//#include "game.h"

//Map *Map::m_map = NULL;

SMapChipLocInfo Info1[] = {

//#include "Boss.h"
#include "locationinfo7.h"
};

SMapChipLocInfo Info2[] = {

//#include "Boss.h"
#include "locationinfo8.h"
};

SMapChipLocInfo Info3[] = {

#include "Boss.h"
	//#include "locationinfo8.h"
};

Map::Map()
{
	MapManager::Create();
}

Map::~Map()
{
	MapManager::GetMapManager().Release();
	//for (auto healnum : m_healList)
	//{
	//	delete healnum;
	//}
	//auto healIt = m_healList.begin();
	//while (healIt != m_healList.end())
	//{
	//	healIt = m_healList.erase(healIt);

	//}
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
	case STAGE::STAGE1://ステージ１
		MapLoad1();
		break;
	case STAGE::STAGE2://ステージ２
		MapLoad2();
		break;
	case STAGE::STAGE3://ステージ3
		MapLoad3();
		break;
	default:
		break;
	}
	
	
}

void Map::Update()
{
	//マップチップを一個ずつ更新。
	MapManager::GetMapManager().Update();

	for (int i = 0; i < m_healList.size(); i++)
	{
		m_healList[i]->Update();
	}

	//回復アイテムを取得したら消去
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
	//マップチップを一個ずつ描画
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
		else if (strcmp(Info1[i].modelName, "TCircle") == 0)//回転　ダメージオブジェクト
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
		else if (strcmp(Info1[i].modelName, "GoalCube") == 0)//ゴール地点
		{
			MapCreate("GoalObject", i, &Info1[0]);
		}
		else if (strcmp(Info1[i].modelName, "HealItem") == 0)//回復アイテム
		{
			HealItem* healChip = new HealItem;
			healChip->Init(Info1[i].modelName, Info1[i].pos, Info1[i].rot);
			m_healList.push_back(healChip);
		}
		else if (strcmp(Info1[i].modelName, "Boss") == 0)
		{
			SceneManager::GetInstance().GetGame().SetBossBattle(true);
			/*BossEnemy* bossEnemy = new BossEnemy;
			BossHp* bossHp = new BossHp;
			bossEnemy->Init(Info1[i].pos, Info1[i].rot);
			bossHp->Init();
			SceneManager::GetGame().CreateBoss(bossEnemy);
			SceneManager::GetGame().CreateBossHp(bossHp);*/
			//GameObjectManager::GetGameObjectManager().AddGameObject(bossEnemy);
			//GameObjectManager::GetGameObjectManager().AddGameObject(bossHp);

			/*BossEnemy::Create();
			BossHp::Create();
			BossEnemy::GetInstance().Init(Info1[i].pos, Info1[i].rot);
			BossHp::GetInstance().Init();

			GameObjectManager::GetGameObjectManager().AddGameObject(&BossEnemy::GetInstance());
			GameObjectManager::GetGameObjectManager().AddGameObject(&BossHp::GetInstance());*/
		}
		else if (strcmp(Info1[i].modelName, "Weapon") == 0)
		{
			/*BulletWeapon* weapon = new BulletWeapon;
			BulletManager::GetInstance().AddBulletWeapon(weapon);
			weapon->Init(Info1[i].pos, Info1[i].rot);*/
		}
		else if (strcmp(Info1[i].modelName, "Drone") == 0)//エネミーの位置設定
		{
			trackingEnemy* Tenemy = new trackingEnemy;
			SceneManager::GetGame().GetEnemyManager().AddTrackingEnemy(Tenemy);
			Tenemy->Init(Info1[i].pos, Info1[i].rot);
		}
		else if (strcmp(Info1[i].modelName, "unity") == 0)//プレイヤーの初期位置
		{
			SceneManager::GetGame().GetPlayer().Setpos(Info1[i].pos);
		}
		else {
			//オブジェクトを一個ずつロードしていく。
			//MapChipのインスタンスを動的に生成。
			//MapChip* mapChip = new MapChip;
			////マップチップの情報を渡して初期化。
			//mapChip->Init(Info1[i].modelName, Info1[i].pos, Info1[i].rotation);
			//動的配列にプッシュ。
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
		else if (strcmp(Info2[i].modelName, "TCircle") == 0)//回転　ダメージオブジェクト
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
		else if (strcmp(Info2[i].modelName, "GoalCube") == 0)//ゴール地点
		{
			MapCreate("GoalObject", i, &Info2[0]);
		}
		else if (strcmp(Info2[i].modelName, "HealItem") == 0)//回復アイテム
		{
			HealItem* healChip = new HealItem;
			healChip->Init(Info2[i].modelName, Info2[i].pos, Info2[i].rot);
			m_healList.push_back(healChip);
		}
		else if (strcmp(Info2[i].modelName, "Boss") == 0)
		{
			SceneManager::GetInstance().GetGame().SetBossBattle(true);
			/*BossEnemy* bossEnemy = new BossEnemy;
			BossHp* bossHp = new BossHp;
			bossEnemy->Init(Info1[i].pos, Info1[i].rot);
			bossHp->Init();
			SceneManager::GetGame().CreateBoss(bossEnemy);
			SceneManager::GetGame().CreateBossHp(bossHp);
			GameObjectManager::GetGameObjectManager().AddGameObject(bossEnemy);
			GameObjectManager::GetGameObjectManager().AddGameObject(bossHp);*/
		}
		else if (strcmp(Info1[i].modelName, "Weapon") == 0)
		{
			/*BulletWeapon* weapon = new BulletWeapon;
			BulletManager::GetInstance().AddBulletWeapon(weapon);
			weapon->Init(Info1[i].pos, Info1[i].rot);*/
		}
		else if (strcmp(Info2[i].modelName, "Drone") == 0)//エネミーの位置設定
		{
			trackingEnemy* Tenemy = new trackingEnemy;
			SceneManager::GetGame().GetEnemyManager().AddTrackingEnemy(Tenemy);
			Tenemy->Init(Info2[i].pos, Info2[i].rot);
		}
		else if (strcmp(Info2[i].modelName, "unity") == 0)//プレイヤーの初期位置
		{
			SceneManager::GetGame().GetPlayer().Setpos(Info2[i].pos);
		}
		else {
			MapCreate("map", i, &Info2[0]);
		}

	}
}

void Map::MapLoad3()
{
	int numObject = sizeof(Info3) / sizeof(Info3[0]);

	for (int i = 0; i < numObject; i++) {

		if (strcmp(Info3[i].modelName, "dore") == 0)
		{
			MapCreate("MoveObject", i, &Info3[0]);
		}
		else if (strcmp(Info3[i].modelName, "BCube") == 0)
		{
			MapCreate("BoxChip", i, &Info3[0]);
		}
		else if (strcmp(Info3[i].modelName, "BCube2") == 0)
		{
			MapCreate("BoxChip", i, &Info3[0]);
		}
		else if (strcmp(Info3[i].modelName, "TCircle") == 0)//回転　ダメージオブジェクト
		{
			MapCreate("TCircle", i, &Info3[0]);
		}
		else if (strcmp(Info3[i].modelName, "FCubeF") == 0)
		{
			MapCreate("FCubeF", i, &Info3[0]);
		}
		else if (strcmp(Info3[i].modelName, "FCubeB") == 0)
		{
			MapCreate("FCubeB", i, &Info3[0]);
		}
		else if (strcmp(Info3[i].modelName, "FCubeR") == 0)
		{
			MapCreate("FCubeR", i, &Info3[0]);
		}
		else if (strcmp(Info3[i].modelName, "FCubeL") == 0)
		{
			MapCreate("FCubeL", i, &Info3[0]);
		}
		else if (strcmp(Info3[i].modelName, "GoalCube") == 0)//ゴール地点
		{
			MapCreate("GoalObject", i, &Info3[0]);
		}
		else if (strcmp(Info3[i].modelName, "HealItem") == 0)//回復アイテム
		{
			HealItem* healChip = new HealItem;
			healChip->Init(Info3[i].modelName, Info3[i].pos, Info3[i].rot);
			m_healList.push_back(healChip);
		}
		else if (strcmp(Info3[i].modelName, "Boss") == 0)
		{
			SceneManager::GetInstance().GetGame().SetBossBattle(true);
			/*BossEnemy* bossEnemy = new BossEnemy;
			BossHp* bossHp = new BossHp;
			bossEnemy->Init(Info1[i].pos, Info1[i].rot);
			bossHp->Init();
			SceneManager::GetGame().CreateBoss(bossEnemy);
			SceneManager::GetGame().CreateBossHp(bossHp);
			GameObjectManager::GetGameObjectManager().AddGameObject(bossEnemy);
			GameObjectManager::GetGameObjectManager().AddGameObject(bossHp);*/
		}
		else if (strcmp(Info1[i].modelName, "Weapon") == 0)
		{
			/*BulletWeapon* weapon = new BulletWeapon;
			BulletManager::GetInstance().AddBulletWeapon(weapon);
			weapon->Init(Info1[i].pos, Info1[i].rot);*/
		}
		else if (strcmp(Info3[i].modelName, "Drone") == 0)//エネミーの位置設定
		{
			trackingEnemy* Tenemy = new trackingEnemy;
			SceneManager::GetGame().GetEnemyManager().AddTrackingEnemy(Tenemy);
			Tenemy->Init(Info3[i].pos, Info3[i].rot);
		}
		else if (strcmp(Info3[i].modelName, "unity") == 0)//プレイヤーの初期位置
		{
			SceneManager::GetGame().GetPlayer().Setpos(Info3[i].pos);
		}
		else {
			MapCreate("map", i, &Info3[0]);
		}

	}
}