#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"
#include "MapObject.h"
#include "MoveObject.h"
#include "TrapObject.h"
#include "RotObject.h"
#include "FallObject.h"
#include "GoalObject.h"
#include "HealItem.h"
#include "MoveCube.h"
#include "Spring.h"
#include "GravityObject.h"
#include "Sea.h"
#include "Sky.h"

struct SMapChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
};

SMapChipLocInfo mapChipInfo[] = {
#include "locationinfo5.h"
};

SMapChipLocInfo mapChipInfo2[] = {
#include "locationinfo2.h"
};

Map::Map()
{
}

Map::~Map()
{
	for (auto mapnum : m_mapList)
	{
		delete mapnum;
	}
	auto mapIt = m_mapList.begin();
	while (mapIt != m_mapList.end())
	{
		mapIt = m_mapList.erase(mapIt);
	}
}

void Map::Init(/*struct SMapChipLocInfo Info[]*/)
{
	int numObject=0;
	SMapChipLocInfo work[2000];

	switch (m_stageNum)
	{
	case STAGE1://ステージ１
		numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);
		for (int i = 0; i < numObject; i++)
		{
			work[i] = mapChipInfo[i];
		}
		break;
	case STAGE2://ステージ２
		numObject = sizeof(mapChipInfo2) / sizeof(mapChipInfo2[0]);
		for (int i = 0; i < numObject; i++)
		{
			work[i] = mapChipInfo2[i];
		}
		break;
	default:
		break;
	}

	for (int i = 0; i < numObject; i++) {

		if (strcmp(work[i].modelName, "MCube") == 0)//十字床
		{
			MoveObject* moveChip = new MoveObject;
			moveChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//moveList.push_back(moveChip);
			m_mapList.push_back(moveChip);
		}
		else if (strcmp(work[i].modelName, "FORWARDCube") == 0)//前進する移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->FORWARD, {-48.0f,0.0f,0.0f});
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			m_mapList.push_back(mCubeChip);

		}
		else if (strcmp(work[i].modelName, "LEFTCube") == 0)//左移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->LEFT, { 0.0f,0.0f,-24.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			m_mapList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "RIGHTCube") == 0)//右移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->RIGHT, { 0.0f,0.0f,24.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			m_mapList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "BACKCube") == 0)//後移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->BACK, { -9.0f,0.0f,0.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			m_mapList.push_back(mCubeChip);

		}
		else if (strcmp(work[i].modelName, "DOWNCube") == 0)//下移動床
		{
			MoveCube* mCubeChip = new MoveCube(mCubeChip->DOWN, { 0.0f,-10.0f,0.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			m_mapList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "UPCube") == 0)//上移動床
		{
			MoveCube* mCubeChip = new MoveCube(mCubeChip->DOWN, { 0.0f,10.0f,0.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			m_mapList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "TCircle") == 0)//回転　ダメージオブジェクト
		{
			m_rDir = { 0.0f,1.0f,0.0f };
			TrapObject* trapChip = new TrapObject(trapChip->ROT,m_rDir);
			trapChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//trapList.push_back(trapChip);
			m_mapList.push_back(trapChip);

		}
		else if (strcmp(work[i].modelName, "RCube") == 0)//回転オブジェクト
		{
			m_rDir = { 0.0f,0.0f,1.0f };
			m_rSpeed = { -4.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "LCube") == 0)//回転オブジェクト
		{
			m_rDir = { 0.0f,0.0f,-1.0f };
			m_rSpeed = { 4.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "CubeL") == 0)//回転オブジェクト2
		{
			m_rDir = { 1.0f,0.0f,0.0f };
			m_rSpeed = { 0.0f,0.0f,4.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "CubeR") == 0)//回転オブジェクト3
		{
			m_rDir = { -1.0f,0.0f,0.0f };
			m_rSpeed = { 0.0f,0.0f,-4.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "block") == 0)//回転オブジェクト3
		{
			m_rDir = { 0.0f,1.0f,0.0f };
			m_rSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "block2") == 0)//回転オブジェクト3
		{
			m_rDir = { 0.0f,-1.0f,0.0f };
			m_rSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "block3") == 0)//回転オブジェクト3
		{
			m_rDir = { 0.0f,1.0f,0.0f };
			m_rSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "WRole") == 0)//回転オブジェクト3
		{
			m_rDir = { 0.0f,1.0f,0.0f };
			m_rSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(m_rDir,m_rSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "Cube_L") == 0)//回転オブジェクト4
		{
			m_rDir = { 0.0f,1.0f,0.0f };
			m_rSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "Cube_R") == 0)//回転オブジェクト4
		{
			m_rDir = { 0.0f,-1.0f,0.0f };
			m_rSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			m_mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "ClocksinB") == 0)//回転オブジェクト4
		{
			m_rDir = { 1.0f,0.0f,0.0f };
			m_rSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(m_rDir, m_rSpeed,rotChip->CLOCK);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			m_mapList.push_back(rotChip);
		}
		else if (strcmp(work[i].modelName, "FCube") == 0)//落下オブジェクト
		{
			FallObject* fallChip = new FallObject;
			fallChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//fallList.push_back(fallChip);
			m_mapList.push_back(fallChip);
		}
		else if (strcmp(work[i].modelName, "HealItem") == 0|| strcmp(work[i].modelName, "apple") == 0 
			|| strcmp(work[i].modelName, "banana") == 0 || strcmp(work[i].modelName, "cake") == 0 
			|| strcmp(work[i].modelName, "grape") == 0 || strcmp(work[i].modelName, "cherry") == 0)//回復アイテム
		{
			HealItem* healChip = new HealItem;
			healChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			m_healList.push_back(healChip);
			//m_mapList.push_back(healChip);
		}
		else if (strcmp(work[i].modelName, "GoalCube") == 0)//ゴール地点
		{
			GoalObject* goalChip = new GoalObject;
			goalChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//GoalList.push_back(goalChip);
			m_mapList.push_back(goalChip);
		}
		else if (strcmp(work[i].modelName, "Bane") == 0)//
		{
			Spring* SpringChip = new Spring;
			SpringChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			m_mapList.push_back(SpringChip);
		}
		else if (strcmp(work[i].modelName, "GCube") == 0)//重力キューブ
		{
			GravityObject* GravityChip = new GravityObject;
			GravityChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			m_mapList.push_back(GravityChip);
		}
		else if (strcmp(work[i].modelName, "sky")==0)//空
		{
			Sky* skyChip = new Sky;
			skyChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			m_mapList.push_back(skyChip);
		}
		else if (strcmp(work[i].modelName, "Sea") == 0)//海
		{
			Sea* seaChip = new Sea;
			seaChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//seaList.push_back(seaChip);
			m_mapList.push_back(seaChip);
		}
		else if (strcmp(work[i].modelName, "Enemy") == 0)//エネミーの位置設定
		{
			Enemy* enemy = new Enemy;
			g_game->AddEnemy(enemy);
			enemy->Start(work[i].pos);
		}
		else if (strcmp(work[i].modelName, "TEnemy") == 0)//追従エネミーの位置設定
		{
			trackingEnemy* Tenemy = new trackingEnemy;
			g_game->AddTEnemy(Tenemy);
			//work[i].modelName = "ghost.X";
			Tenemy->Start(work[i].pos, work[i].rotation);
		}
		else if (strcmp(work[i].modelName, "unity") == 0)//プレイヤーの初期位置
		{
			g_game->GetPlayer()->Setpos(work[i].pos);
		}
		else {
			//オブジェクトを一個ずつロードしていく。
			//MapChipのインスタンスを動的に生成。
			MapChip* mapChip = new MapChip;
			//マップチップの情報を渡して初期化。
			mapChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			//mapChipList.push_back(mapChip);
			m_mapList.push_back(mapChip);
		}

	}
}

void Map::Update()
{
	//マップチップを一個ずつ更新。
	for (int i = 0; i < m_mapList.size(); i++)
	{
		m_mapList[i]->Update();
	}

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
	for (int i = 0; i < m_mapList.size(); i++)
	{
		m_mapList[i]->Draw();
	}

	for (int i = 0; i < m_healList.size(); i++)
	{
		m_healList[i]->Draw();
	}

}