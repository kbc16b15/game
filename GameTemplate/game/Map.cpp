#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"
#include "MoveObject.h"
#include "TrapObject.h"
#include "RotObject.h"
#include "FallObject.h"

struct SMapChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;		//回転。
};

SMapChipLocInfo mapChipInfo[] = {
#include "locationinfo.h"
};

Map::Map()
{
}

Map::~Map()
{
}
void Map::Init()
{
	//配置されているオブジェクトの数を計算。
	int numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);
	for (int i = 0; i < numObject; i++) {

		//if (strcmp(mapChipInfo[i].modelName, "NCube") == 0)
		//{
		//	MapChip* mapChip = new MapChip;
		//	//マップチップの情報を渡して初期化。
		//	mapChip->Init(mapChipInfo[i].modelName, mapChipInfo[i].pos, mapChipInfo[i].rotation);
		//	//動的配列にプッシュ。
		//	mapChipList.push_back(mapChip);
		//	mapChip->Rend(true);
		//}
		/*else */if (strcmp(mapChipInfo[i].modelName, "MCube") == 0)
		{

			MoveObject* moveChip = new MoveObject;
			//マップチップの情報を渡して初期化。
			moveChip->Init(mapChipInfo[i].modelName, mapChipInfo[i].pos, mapChipInfo[i].rotation);
			//動的配列にプッシュ。
			moveList.push_back(moveChip);

		}
		else if (strcmp(mapChipInfo[i].modelName, "TCircle") == 0)
		{
			RDir = { 0.0f,1.0f,0.0f };
			TrapObject* trapChip = new TrapObject(RDir);
			//マップチップの情報を渡して初期化。
			trapChip->Init(mapChipInfo[i].modelName, mapChipInfo[i].pos, mapChipInfo[i].rotation);
			//動的配列にプッシュ。
			trapList.push_back(trapChip);

		}
		else if ( strcmp(mapChipInfo[i].modelName, "RCube") == 0)
		{
			RDir = { 0.0f,0.0f,1.0f };
			RSpeed = {-7.0f,0.0f,0.0f};
			RotObject* rotChip = new RotObject(RDir,RSpeed);
			//マップチップの情報を渡して初期化。
			rotChip->Init(mapChipInfo[i].modelName, mapChipInfo[i].pos, mapChipInfo[i].rotation);
			//動的配列にプッシュ。
			rotList.push_back(rotChip);

		}
		else if (strcmp(mapChipInfo[i].modelName, "Enemy") == 0)
		{

			Enemy* enemy = new Enemy;
			game->AddEnemy(enemy);
			enemy->Start(mapChipInfo[i].pos);

		}
		else if (strcmp(mapChipInfo[i].modelName, "FCube") == 0)
		{
			FallObject* fallChip = new FallObject;
			fallChip->Init(mapChipInfo[i].modelName, mapChipInfo[i].pos, mapChipInfo[i].rotation);
			fallList.push_back(fallChip);
		}
		else {
			//オブジェクトを一個ずつロードしていく。
			//まずはMapChipのインスタンスを動的に生成。
			MapChip* mapChip = new MapChip;
			//マップチップの情報を渡して初期化。
			mapChip->Init(mapChipInfo[i].modelName, mapChipInfo[i].pos, mapChipInfo[i].rotation);
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
}


