#pragma once
#include "myEngine/Physics/CollisionAttr.h"
class MapObject
{
public:
	//�R���X�g���N�^
	MapObject();
	//�f�X�g���N�^
	virtual ~MapObject();
	//���N���X�̃C�j�b�g
	//virtual void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation)=0;
	//���N���X�̃A�b�v�f�[�g
	virtual void Update()=0;
	//���N���X�̃h���E
	virtual void Draw()=0;
//protected:
//	SkinModel		model;					//�X�L�����f��
//	SkinModelData	modelData;				//�X�L�����f���f�[�^
//	D3DXVECTOR3		position;				//���W
//	D3DXQUATERNION	rotation;				//��]
//	Light			light;					//���C�g
//	MeshCollider	meshCollider;			//���b�V���R���C�_�[
//	RigidBody		rigidBody;				//���́B
//	RigidBodyInfo	rbInfo;					//���̏��
};

