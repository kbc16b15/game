#pragma once
#include "MapObject.h"
class GravityObject :
	public MapObject
{
public:
	GravityObject();
	~GravityObject();

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
	D3DXVECTOR3			position;				//���W
	D3DXQUATERNION		rotation;				//��]
	Light				light;					//���C�g
	MeshCollider		meshCollider;			//���b�V���R���C�_�[
	RigidBody			rigidBody;				//���́B
	RigidBodyInfo		rbInfo;					//���̏��
	bool				Gflg = false;			//�͈̓t���O
	float				SpringSpeed = 10.0f;	//�o�l���x
	const float			length = 1.0f;			//�͈�
	int					GravityTime = 0;		//���]����
	CharacterController	characterController;	//�L�����N�^�[�R���g���[���[
};
