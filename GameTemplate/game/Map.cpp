#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"
#include "MoveObject.h"
#include "TrapObject.h"
#include "RotObject.h"
#include "FallObject.h"
#include "GoalObject.h"
#include "HealItem.h"
#include "Sky.h"
#include "MoveCube.h"

struct SMapChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
};

SMapChipLocInfo mapChipInfo[] = {
	#include "locationinfo2.h"
};

SMapChipLocInfo mapChipInfo2[] = {
	#include "locationinfo3.h"
};

Map::Map()
{
}

Map::~Map()
{
	auto mapChipIt = mapChipList.begin();
	while (mapChipIt != mapChipList.end()) {
		
		mapChipIt = mapChipList.erase(mapChipIt);
	}

	auto moveIt = moveList.begin();
	while (moveIt != moveList.end()) {

		moveIt = moveList.erase(moveIt);
	}

	auto trapIt = trapList.begin();
	while (trapIt != trapList.end()) {

		trapIt = trapList.erase(trapIt);
	}

	auto rotIt = rotList.begin();
	while (rotIt != rotList.end()) {

		rotIt = rotList.erase(rotIt);
	}

	auto fallIt = fallList.begin();
	while (fallIt != fallList.end()) {

		fallIt = fallList.erase(fallIt);
	}

	auto GoalIt = GoalList.begin();
	while (GoalIt != GoalList.end()) {

		GoalIt = GoalList.erase(GoalIt);
	}
}

void Map::Init(/*struct SMapChipLocInfo Info[]*/)
{
	int numObject;
	SMapChipLocInfo work[1000];
	switch (m_StageNum)
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
	}
	for (int i = 0; i < numObject; i++) {

		if (strcmp(work[i].modelName, "MCube") == 0)//十字床
		{

			MoveObject* moveChip = new MoveObject;
			//マップチップの情報を渡して初期化。
			moveChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			moveList.push_back(moveChip);

		}
		else if (strcmp(work[i].modelName, "FORWARDCube") == 0)//前進する移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->FORWARD, {-48.0f,0.0f,0.0f});
			//マップチップの情報を渡して初期化。
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			mCubeList.push_back(mCubeChip);

		}
		else if (strcmp(work[i].modelName, "LEFTCube") == 0)//左移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->LEFT, { 0.0f,0.0f,-24.0f });
			//マップチップの情報を渡して初期化。
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			mCubeList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "RIGHTCube") == 0)//右移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->RIGHT, { 0.0f,0.0f,24.0f });
			//マップチップの情報を渡して初期化。
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			mCubeList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "BACKCube") == 0)//後移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->BACK, { -9.0f,0.0f,0.0f });
			//マップチップの情報を渡して初期化。
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			mCubeList.push_back(mCubeChip);

		}
		else if (strcmp(work[i].modelName, "DOWNCube") == 0)//下移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->DOWN, { 0.0f,-10.0f,0.0f });
			//マップチップの情報を渡して初期化。
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			mCubeList.push_back(mCubeChip);

		}
		else if (strcmp(work[i].modelName, "UPCube") == 0)//上移動床
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->DOWN, { 0.0f,10.0f,0.0f });
			//マップチップの情報を渡して初期化。
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			mCubeList.push_back(mCubeChip);

		}
		else if (strcmp(work[i].modelName, "TCircle") == 0)//回転　ダメージオブジェクト
		{
			RDir = { 0.0f,1.0f,0.0f };
			TrapObject* trapChip = new TrapObject(trapChip->ROT,RDir);
			//マップチップの情報を渡して初期化。
			trapChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			trapList.push_back(trapChip);

		}
		else if (strcmp(work[i].modelName, "RCube") == 0)//回転オブジェクト
		{
			RDir = { 0.0f,0.0f,1.0f };
			RSpeed = { -7.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed);
			//マップチップの情報を渡して初期化。
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			rotList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "CubeL") == 0)//回転オブジェクト2
		{
			RDir = { 1.0f,0.0f,0.0f };
			RSpeed = { 0.0f,0.0f,4.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed);
			//マップチップの情報を渡して初期化。
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			rotList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "FCube") == 0)//落下オブジェクト
		{
			FallObject* fallChip = new FallObject;
			fallChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			fallList.push_back(fallChip);
		}
		else if (strcmp(work[i].modelName, "HealItem") == 0)//回復アイテム
		{
			HealItem* healChip = new HealItem;
			healChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			HealList.push_back(healChip);
		}
		else if (strcmp(work[i].modelName, "GoalCube") == 0)//ゴール地点
		{
			GoalObject* goalChip = new GoalObject;
			goalChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			GoalList.push_back(goalChip);
		}
		else if (strcmp(work[i].modelName, "Box")==0)//背景のボックス
		{
			Sky* skyChip = new Sky;
			skyChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			skyList.push_back(skyChip);
		}
		else if (strcmp(work[i].modelName, "Enemy") == 0)//エネミーの位置設定？
		{
			Enemy* enemy = new Enemy;
			game->AddEnemy(enemy);
			enemy->Start(work[i].pos);

		}
		else if (strcmp(work[i].modelName, "unity") == 0)//プレイヤーの初期位置
		{
			game->GetPlayer()->Setpos(work[i].pos);
		}
		else {
			//オブジェクトを一個ずつロードしていく。
			//まずはMapChipのインスタンスを動的に生成。
			MapChip* mapChip = new MapChip;
			//マップチップの情報を渡して初期化。
			mapChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//動的配列にプッシュ。
			mapChipList.push_back(mapChip);
		}
	}
}

void Map::Update()
{
	//マップチップを一個ずつ更新。
	for (int i = 0; i < mapChipList.size(); i++)
	{
		mapChipList[i]->Update();
	}

	for (int i = 0; i < moveList.size(); i++)
	{
		moveList[i]->Update();
	}

	for (int i = 0; i < trapList.size(); i++)
	{
		trapList[i]->Update();
	}

	for (int i = 0; i < rotList.size(); i++)
	{
		rotList[i]->Update();
	}

	for (int i = 0; i < fallList.size(); i++)
	{
		fallList[i]->Update();
	}

	for (int i = 0; i < GoalList.size(); i++)
	{
		GoalList[i]->Update();
	}
	for (int i = 0; i < HealList.size(); i++)
	{
		HealList[i]->Update();
	}
	for (int i = 0; i < skyList.size(); i++)
	{
		skyList[i]->Update();
	}
	for (int i = 0; i < mCubeList.size(); i++)
	{
		mCubeList[i]->Update();
	}

	auto HealIt = HealList.begin();
	while (HealIt != HealList.end()) {
		if ((*HealIt)->GetHeal()) {
			HealIt = HealList.erase(HealIt);
		}
		else {
			HealIt++;
		}
	}
}

void Map::Draw()
{
	//マップチップを一個ずつ描画。
	for (int i = 0; i < mapChipList.size(); i++) {
	/*	if (mapChipList[i]->Rend(false))
		{
			continue;
		}*/

		mapChipList[i]->Draw();

	}

	for (int i = 0; i < moveList.size(); i++)
	{
		moveList[i]->Draw();
	}

	for (int i = 0; i < trapList.size(); i++)
	{
		trapList[i]->Draw();
	}

	for (int i = 0; i < rotList.size(); i++)
	{
		rotList[i]->Draw();
	}

	for (int i = 0; i < fallList.size(); i++)
	{
		fallList[i]->Draw();
	}

	for (int i = 0;i < GoalList.size();i++)
	{
		GoalList[i]->Draw();
	}
	for (int i = 0;i < HealList.size();i++)
	{
		HealList[i]->Draw();
	}
	for (int i = 0;i < skyList.size();i++)
	{
		skyList[i]->Draw();
	}
	for (int i = 0;i < mCubeList.size();i++)
	{
		mCubeList[i]->Draw();
	}
}


