#pragma once
#include "MapObject.h"
class TrapObject :public MapObject
{
public:
	TrapObject(int Damagetype,D3DXVECTOR3 RDir);
	~TrapObject();
	//������
	//modelName ���f����
	//pos		���f���̍��W
	//rotation	���f���̉�]
	void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();

	void Rot();
	//���W�̎擾
	D3DXVECTOR3 Getpos()
	{
		return position;
	}

	enum DamageObjectType {
		STAND,
		ROT,
		MOVE,
	};
private:
	int DamageType = STAND;
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
	float			angle = 0.0f;			//�p�x
	bool			rotflg = false;
};