#pragma once
#include "MapObject.h"
class RotObject :public MapObject
{
public:
	RotObject(D3DXVECTOR3 RDir,D3DXVECTOR3 RSpeed,int Rottype);
	RotObject(D3DXVECTOR3 RDir, D3DXVECTOR3 RSpeed);
	~RotObject();

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

	enum RotObjectType{
		ROT,
		CLOCK,
		STAND
	};
private:
	int RotType = ROT;
	SkinModel		model;					//�X�L�����f��
	SkinModelData	modelData;				//�X�L�����f���f�[�^
	D3DXVECTOR3		position;				//���W
	D3DXQUATERNION	rotation;				//��]
	Light			light;					//���C�g
	MeshCollider	meshCollider;			//���b�V���R���C�_�[
	RigidBody		rigidBody;				//���́B
	RigidBodyInfo	rbInfo;					//���̏��
	D3DXVECTOR3		RotDir;					//��]����
	D3DXVECTOR3		RotSpeed;				//��]���x
	float angle = 0.0f;						//�p�x
	bool Tflg = false;						//�v���C���[�Ƃ̃t���O
	const float length = 8.0f;				//�Ђ�����͈�

	int ClockRotTime = 200;

	float x = 0.0f;
	float z = 0.0f;
};

