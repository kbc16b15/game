#pragma once
//#include "IGameObject.h"
#include "MapObject.h"
class MapChip :public MapObject
{
public:
	//�R���X�g���N�^
	MapChip();
	//�f�X�g���N�^
	~MapChip();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�`��̖�����ݒ�
	//Rendflg�@�`��t���O
	//bool Rend(bool Rendflg);

private:
	MapObject*			mapObject;
	SkinModel			model;					//�X�L�����f��
	SkinModelData		modelData;				//�X�L�����f���f�[�^
	D3DXVECTOR3			position;				//���W
	D3DXQUATERNION		rotation;				//��]
	Light				light;					//���C�g
	MeshCollider		meshCollider;			//���b�V���R���C�_�[
	//CapsuleCollider	capsuleCollider;		//�J�v�Z���R���C�_�[
	RigidBody			rigidBody;				//���́B
	RigidBodyInfo		rbInfo;					//���̏��
	//bool				Render = false;			//�`��t���O

};

