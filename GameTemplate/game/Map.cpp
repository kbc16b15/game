#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"

static SMapChipLocInfo mapChipInfo[] = {
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

		if (strcmp(mapChipInfo[i].modelName, "NCube") == 0)
		{

			MapChip* mapChip = new MapChip;
			//マップチップの情報を渡して初期化。
			mapChip->Init(mapChipInfo[i]);
			//動的配列にプッシュ。
			mapChipList.push_back(mapChip);

			mapChip->Rend(true);
		}
		else {
			//オブジェクトを一個ずつロードしていく。
			//まずはMapChipのインスタンスを動的に生成。
			MapChip* mapChip = new MapChip;
			//マップチップの情報を渡して初期化。
			mapChip->Init(mapChipInfo[i]);
			//動的配列にプッシュ。
			mapChipList.push_back(mapChip);
		}
	}



}
void Map::Update()
{
	//マップチップを一個ずつ更新。
	for (int i = 0; i < mapChipList.size(); i++) {
		mapChipList[i]->Update();
	}
}
void Map::Draw()
{
	//マップチップを一個ずつ描画。
	for (int i = 0; i < mapChipList.size(); i++) {
		if (mapChipList[i]->Rend(false))
		{
			continue;
		}
		mapChipList[i]->Draw();
	}
}

