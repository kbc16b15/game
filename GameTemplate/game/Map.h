#pragma once
//#include "IGameObject.h"
class MapChip;
class MoveObject;
class TrapObject;
class RotObject;
class FallObject;
class Map/*:public IGameObject*/
{
public:
	//�R���X�g���N�^
	Map();
	//�f�X�g���N�^
	~Map();
	//������
	void Init();
	//�`��
	void Draw();
	//�X�V
	void Update();
	
	//���[�u�I�u�W�F�N�g�̃��X�g�̎擾
	//�߂�l�@std::vector<MoveObject*>
	//std::vector<MoveObject*>& GetMobject()
	//{
	//	return moveList;
	//}
private:
	std::vector<MapChip*>	mapChipList;	//�}�b�v�`�b�v�̃��X�g�B
	std::vector<MoveObject*> moveList;		//���[�u�I�u�W�F�N�g�̃��X�g
	std::vector<TrapObject*> trapList;		//�_���[�W�I�u�W�F�N�g�̃��X�g
	std::vector<RotObject*> rotList;		//��]�I�u�W�F�N�g�̃��X�g
	std::vector<FallObject*> fallList;		//�����I�u�W�F�N�g�̃��X�g

	D3DXVECTOR3 RDir = { 0.0f,1.0f,0.0f };	//��]�̌���
	D3DXVECTOR3 RSpeed= { 0.0f,1.0f,0.0f };	//��]���x


};
