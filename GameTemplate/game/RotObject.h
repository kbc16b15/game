#pragma once
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
class RotObject
{
public:
	RotObject(D3DXVECTOR3 RDir,D3DXVECTOR3 RSpeed);
	~RotObject();

	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//���W�̎擾
	D3DXVECTOR3 Getpos()
	{
		return position;
	}

private:
	SkinModel		model;					//�X�L�����f��
	SkinModelData	modelData;				//�X�L�����f���f�[�^
	D3DXVECTOR3		position;				//���W
	D3DXQUATERNION	Rotation;				//��]
	Light			light;					//���C�g
	MeshCollider	meshCollider;			//���b�V���R���C�_�[
	RigidBody		rigidBody;				//���́B
	RigidBodyInfo	rbInfo;					//���̏��
	//CharacterController	characterController;//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3		RotDir;					//��]����
	D3DXVECTOR3		RotSpeed;				//��]���x
	float angle = 0.0f;						//�p�x
	bool Tflg = false;						//�v���C���[�Ƃ̃t���O
};

