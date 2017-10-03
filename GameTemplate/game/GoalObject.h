#pragma once
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/CapsuleCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
class GoalObject
{
public:
	//�R���X�g���N�^
	GoalObject();
	//�f�X�g���N�^
	~GoalObject();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�`��̖�����ݒ�

private:
	SkinModel			model;							//�X�L�����f��
	SkinModelData		modelData;						//�X�L�����f���f�[�^
	D3DXVECTOR3			position;						//���W
	D3DXQUATERNION		rotation;						//��]
	Light				light;							//���C�g
	MeshCollider		meshCollider;					//���b�V���R���C�_�[
	RigidBody			rigidBody;						//���́B
	RigidBodyInfo		rbInfo;							//���̏��
	CharacterController	characterController;			//�L�����N�^�[�R���g���[���[
};

