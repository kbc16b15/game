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
#include "MapObject.h"
#include "Spring.h"
#include "GravityObject.h"
#include "Sea.h"

struct SMapChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
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
	auto mapIt = mapList.begin();
	while (mapIt != mapList.end())
	{
		mapIt = mapList.erase(mapIt);
	}
}

void Map::Init(/*struct SMapChipLocInfo Info[]*/)
{
	int numObject=0;
	SMapChipLocInfo work[1000];

	switch (m_StageNum)
	{
	case STAGE1://�X�e�[�W�P
		numObject = sizeof(mapChipInfo) / sizeof(mapChipInfo[0]);
		for (int i = 0; i < numObject; i++)
		{
			work[i] = mapChipInfo[i];
		}
		break;
	case STAGE2://�X�e�[�W�Q
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

		if (strcmp(work[i].modelName, "MCube") == 0)//�\����
		{
			MoveObject* moveChip = new MoveObject;
			moveChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//moveList.push_back(moveChip);
			mapList.push_back(moveChip);
		}
		else if (strcmp(work[i].modelName, "FORWARDCube") == 0)//�O�i����ړ���
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->FORWARD, {-48.0f,0.0f,0.0f});
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			mapList.push_back(mCubeChip);

		}
		else if (strcmp(work[i].modelName, "LEFTCube") == 0)//���ړ���
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->LEFT, { 0.0f,0.0f,-24.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			mapList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "RIGHTCube") == 0)//�E�ړ���
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->RIGHT, { 0.0f,0.0f,24.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			mapList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "BACKCube") == 0)//��ړ���
		{

			MoveCube* mCubeChip = new MoveCube(mCubeChip->BACK, { -9.0f,0.0f,0.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			mapList.push_back(mCubeChip);

		}
		else if (strcmp(work[i].modelName, "DOWNCube") == 0)//���ړ���
		{
			MoveCube* mCubeChip = new MoveCube(mCubeChip->DOWN, { 0.0f,-10.0f,0.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			mapList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "UPCube") == 0)//��ړ���
		{
			MoveCube* mCubeChip = new MoveCube(mCubeChip->DOWN, { 0.0f,10.0f,0.0f });
			mCubeChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//mCubeList.push_back(mCubeChip);
			mapList.push_back(mCubeChip);
		}
		else if (strcmp(work[i].modelName, "TCircle") == 0)//��]�@�_���[�W�I�u�W�F�N�g
		{
			RDir = { 0.0f,1.0f,0.0f };
			TrapObject* trapChip = new TrapObject(trapChip->ROT,RDir);
			trapChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//trapList.push_back(trapChip);
			mapList.push_back(trapChip);

		}
		else if (strcmp(work[i].modelName, "RCube") == 0)//��]�I�u�W�F�N�g
		{
			RDir = { 0.0f,0.0f,1.0f };
			RSpeed = { -4.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "LCube") == 0)//��]�I�u�W�F�N�g
		{
			RDir = { 0.0f,0.0f,-1.0f };
			RSpeed = { 4.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "CubeL") == 0)//��]�I�u�W�F�N�g2
		{
			RDir = { 1.0f,0.0f,0.0f };
			RSpeed = { 0.0f,0.0f,4.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "CubeR") == 0)//��]�I�u�W�F�N�g3
		{
			RDir = { -1.0f,0.0f,0.0f };
			RSpeed = { 0.0f,0.0f,-4.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "block") == 0)//��]�I�u�W�F�N�g3
		{
			RDir = { 0.0f,1.0f,0.0f };
			RSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "block2") == 0)//��]�I�u�W�F�N�g3
		{
			RDir = { 0.0f,-1.0f,0.0f };
			RSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "block3") == 0)//��]�I�u�W�F�N�g3
		{
			RDir = { 0.0f,1.0f,0.0f };
			RSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "WRole") == 0)//��]�I�u�W�F�N�g3
		{
			RDir = { 0.0f,1.0f,0.0f };
			RSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "Cube_L") == 0)//��]�I�u�W�F�N�g4
		{
			RDir = { 0.0f,1.0f,0.0f };
			RSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "Cube_R") == 0)//��]�I�u�W�F�N�g4
		{
			RDir = { 0.0f,-1.0f,0.0f };
			RSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed, rotChip->STAND);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			mapList.push_back(rotChip);

		}
		else if (strcmp(work[i].modelName, "ClocksinB") == 0)//��]�I�u�W�F�N�g4
		{
			RDir = { 1.0f,0.0f,0.0f };
			RSpeed = { 0.0f,0.0f,0.0f };
			RotObject* rotChip = new RotObject(RDir, RSpeed,rotChip->CLOCK);
			rotChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//rotList.push_back(rotChip);
			mapList.push_back(rotChip);
		}
		else if (strcmp(work[i].modelName, "FCube") == 0)//�����I�u�W�F�N�g
		{
			FallObject* fallChip = new FallObject;
			fallChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//fallList.push_back(fallChip);
			mapList.push_back(fallChip);
		}
		else if (strcmp(work[i].modelName, "HealItem") == 0)//�񕜃A�C�e��
		{
			HealItem* healChip = new HealItem;
			healChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			HealList.push_back(healChip);
			//mapList.push_back(healChip);
		}
		else if (strcmp(work[i].modelName, "GoalCube") == 0)//�S�[���n�_
		{
			GoalObject* goalChip = new GoalObject;
			goalChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//GoalList.push_back(goalChip);
			mapList.push_back(goalChip);
		}
		else if (strcmp(work[i].modelName, "Bane") == 0)//
		{
			Spring* SpringChip = new Spring;
			SpringChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			mapList.push_back(SpringChip);
		}
		else if (strcmp(work[i].modelName, "GCube") == 0)//�d�̓L���[�u
		{
			GravityObject* GravityChip = new GravityObject;
			GravityChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			mapList.push_back(GravityChip);
		}
		else if (strcmp(work[i].modelName, "sky")==0)//��
		{
			Sky* skyChip = new Sky;
			skyChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//skyList.push_back(skyChip);
			mapList.push_back(skyChip);
		}
		else if (strcmp(work[i].modelName, "Sea") == 0)//�C
		{
			Sea* seaChip = new Sea;
			seaChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//seaList.push_back(seaChip);
			mapList.push_back(seaChip);
		}
		else if (strcmp(work[i].modelName, "Enemy") == 0)//�G�l�~�[�̈ʒu�ݒ�
		{
			Enemy* enemy = new Enemy;
			game->AddEnemy(enemy);
			enemy->Start(work[i].pos);
		}
		else if (strcmp(work[i].modelName, "TEnemy") == 0)//�Ǐ]�G�l�~�[�̈ʒu�ݒ�
		{
			trackingEnemy* Tenemy = new trackingEnemy;
			game->AddTEnemy(Tenemy);
			Tenemy->Start(work[i].pos);
		}
		else if (strcmp(work[i].modelName, "unity") == 0)//�v���C���[�̏����ʒu
		{
			//Player* player = new Player;
			//player->Setpos(work[i].pos);
			//game->GetPlayer()->
			game->GetPlayer()->Setpos(work[i].pos);
		}
		else {
			//�I�u�W�F�N�g��������[�h���Ă����B
			//MapChip�̃C���X�^���X�𓮓I�ɐ����B
			MapChip* mapChip = new MapChip;
			//�}�b�v�`�b�v�̏���n���ď������B
			mapChip->Init(work[i].modelName, work[i].pos, work[i].rotation);
			//���I�z��Ƀv�b�V���B
			//mapChipList.push_back(mapChip);
			mapList.push_back(mapChip);
		}

	}
}

void Map::Update()
{
	//�}�b�v�`�b�v������X�V�B
	for (int i = 0; i < mapList.size(); i++)
	{
		mapList[i]->Update();
	}

	for (int i = 0; i < HealList.size(); i++)
	{
		HealList[i]->Update();
	}

	//�񕜃A�C�e�����擾���������
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
	//�}�b�v�`�b�v������`��
	for (int i = 0; i < mapList.size(); i++)
	{
		mapList[i]->Draw();
	}

	for (int i = 0; i < HealList.size(); i++)
	{
		HealList[i]->Draw();
	}

}