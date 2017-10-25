#pragma once
#include "MapObject.h"
class FallObject:public MapObject
{
public:
	FallObject();
	~FallObject();

	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
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
	SkinModel		model;							//�X�L�����f��
	SkinModelData	modelData;						//�X�L�����f���f�[�^
	D3DXVECTOR3		position;						//���W
	D3DXVECTOR3		firstpos;						//�������W
	D3DXQUATERNION	Rotation;						//��]
	Light			light;							//���C�g
	MeshCollider	meshCollider;					//���b�V���R���C�_�[
	RigidBody		rigidBody;						//���́B
	RigidBodyInfo	rbInfo;							//���̏��
	D3DXVECTOR3		RotDir = {0.0f, 0.0f, 1.0f};	//��]����
	D3DXVECTOR3		RotSpeed;						//��]���x
	float			angle = 0.0f;					//�p�x
	const float		FallSpeedx = 0.05f;
	const float		FallSpeedy = 0.05f;
};

