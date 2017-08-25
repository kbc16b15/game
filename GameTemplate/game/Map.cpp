#include "stdafx.h"
#include "game.h"
#include "Map.h"
#include "MapChip.h"
#include "MoveObject.h"

struct SMapChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;		//��]�B
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
	//�z�u����Ă���I�u�W�F�N�g�̐����v�Z�B
	int numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);
	for (int i = 0; i < numObject; i++) {

		if (strcmp(mapChipInfo[i].modelName, "NCube") == 0)
		{
			MapChip* mapChip = new MapChip;
			//�}�b�v�`�b�v�̏���n���ď������B
			mapChip->Init(mapChipInfo[i].modelName, mapChipInfo[i].pos, mapChipInfo[i].rotation);
			//���I�z��Ƀv�b�V���B
			mapChipList.push_back(mapChip);

			mapChip->Rend(true);
		}
		else if (strcmp(mapChipInfo[i].modelName, "MCube") == 0)
		{

			MoveObject* moveChip = new MoveObject;
			//�}�b�v�`�b�v�̏���n���ď������B

			moveChip->Init(mapChipInfo[i].modelName, mapChipInfo[i].pos, mapChipInfo[i].rotation);
			//���I�z��Ƀv�b�V���B
			moveList.push_back(moveChip);

		}
		else if (strcmp(mapChipInfo[i].modelName, "Enemy") == 0)
		{

			Enemy* enemy = new Enemy;
			game->AddEnemy(enemy);
			enemy->Start(mapChipInfo[i].pos);


		}
		else {
			//�I�u�W�F�N�g��������[�h���Ă����B
			//�܂���MapChip�̃C���X�^���X�𓮓I�ɐ����B
			MapChip* mapChip = new MapChip;
			//�}�b�v�`�b�v�̏���n���ď������B
			mapChip->Init(mapChipInfo[i].modelName, mapChipInfo[i].pos, mapChipInfo[i].rotation);
			//���I�z��Ƀv�b�V���B
			mapChipList.push_back(mapChip);
		}
	}

}

void Map::Update()
{
	//�}�b�v�`�b�v������X�V�B
	for (int i = 0; i < mapChipList.size(); i++)
	{

		mapChipList[i]->Update();
	
	}

	for (int i = 0; i < moveList.size(); i++)
	{

		moveList[i]->Update();

	}

}

void Map::Draw()
{
	//�}�b�v�`�b�v������`��B
	for (int i = 0; i < mapChipList.size(); i++) {
		if (mapChipList[i]->Rend(false))
		{
			continue;
		}

		mapChipList[i]->Draw();

	}

	for (int i = 0; i < moveList.size(); i++)
	{

		moveList[i]->Draw();

	}

}

