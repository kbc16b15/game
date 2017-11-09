#pragma once
#include "MapObject.h"
class Spring :
	public MapObject
{
public:
	Spring();
	~Spring();

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
	SkinModel			model;					//�X�L�����f��
	SkinModelData		modelData;				//�X�L�����f���f�[�^
	Light				light;					//���C�g
	MeshCollider		meshCollider;			//���b�V���R���C�_�[
	RigidBody			rigidBody;				//���́B
	RigidBodyInfo		rbInfo;					//���̏��
	D3DXVECTOR3			position;				//���W
	D3DXQUATERNION		rotation;				//��]
	D3DXVECTOR3			scale = { 1.0f,1.0f,1.0f, };	//�g��
	bool				Sflg = false;			//�͈̓t���O
	float				SpringSpeed=10.0f;		//�o�l���x
	const float			length = 1.5f;			//�Ђ�����͈�
};

