#pragma once
#include "MapObject.h"
class MoveObject :public MapObject
{
public:
	//�R���X�g���N�^
	MoveObject();
	//�f�X�g���N�^
	~MoveObject();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();

	/*void SetMState(int mstate)
	{
		MState = mstate;
	}*/
	//���W�̎擾
	D3DXVECTOR3 Getpos()
	{
		return position;

	}
	//�I�u�W�F�N�g�ɏ���Ă���t���O
	bool GetRide()
	{
		return Rideflg;
	}


private:
	SkinModel		model;						//�X�L�����f��
	SkinModelData	modelData;					//�X�L�����f���f�[�^
	D3DXVECTOR3		position;					//���W
	D3DXQUATERNION	rotation;					//��]
	Light			light;						//���C�g
	MeshCollider	meshCollider;				//���b�V���R���C�_�[
	RigidBody		rigidBody;					//���́B
	RigidBodyInfo	rbInfo;						//���̏��
	CharacterController	characterController;	//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3		UMovelenge = position;
	D3DXVECTOR3		LMovelenge = position;
	D3DXVECTOR3		RMovelenge = position;
	D3DXVECTOR3		DMovelenge = position;
	bool			Render = false;				//�`��t���O
	bool			Rideflg = false;			//��������̃t���O

	bool Rflg = false;
	bool Lflg = false;
	bool Uflg = false;
	bool Dflg = false;

	const float PAddSpeed = 1.2f;
	const float MoveSpeed = 0.02f;
};

