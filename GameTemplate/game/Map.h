#pragma once
//#include "IGameObject.h"

class MapChip;
class MoveObject;
class TrapObject;
class RotObject;
class FallObject;
class GoalObject;
class HealItem;
class Sky;
class MoveCube;
class MapObject;

class Map/*:public IGameObject*/
{
public:
	
	//�R���X�g���N�^
	Map();
	//�f�X�g���N�^
	~Map();
	//������
	void Init(/*struct SMapChipLocInfo Info[]*/);
	//�`��
	void Draw();
	//�X�V
	void Update();

	//void Test(T aa);
	//�X�e�[�W�؂�ւ�
	void SetStage(int StageNum)
	{
		m_StageNum = StageNum;

	}

	//�X�e�[�Wnum
	enum STAGE
	{
		STAGE1,
		STAGE2,
	};
private:
	int m_Stage = STAGE1;
	int m_StageNum=0;
	//std::vector<std::vector<MapChip*>> aa;
	std::vector<MapChip*>	mapChipList;	//�}�b�v�`�b�v�̃��X�g�B
	std::vector<Sky*>		skyList;		//��ƊC
	std::vector<MoveObject*> moveList;		//���[�u�I�u�W�F�N�g�̃��X�g
	std::vector<TrapObject*> trapList;		//�_���[�W�I�u�W�F�N�g�̃��X�g
	std::vector<RotObject*> rotList;		//��]�I�u�W�F�N�g�̃��X�g
	std::vector<FallObject*> fallList;		//�����I�u�W�F�N�g�̃��X�g
	std::vector<GoalObject*> GoalList;		//�S�[���n�_
	std::vector<MoveCube*> mCubeList;		//�ړ���
	std::vector<HealItem*> HealList;		//�񕜃A�C�e��
	std::vector<MapObject*> mapList;		//���N���X�̃��X�g

	D3DXVECTOR3 RDir = { 0.0f,1.0f,0.0f };	//��]�̌���
	D3DXVECTOR3 RSpeed= { 0.0f,1.0f,0.0f };	//��]���x

};