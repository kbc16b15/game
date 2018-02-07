#pragma once
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Physics/MeshCollider.h"
#include "BoxCollider.h"
#include "myEngine\Physics\RigidBody.h"
class MapObject
{
public:
	//�R���X�g���N�^
	MapObject();
	//�f�X�g���N�^
	virtual ~MapObject();
	//���N���X�̃C�j�b�g
	virtual void Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//���N���X�̃A�b�v�f�[�g
	virtual void Update();
	//���N���X�̃h���E
	virtual void Draw();
	MapObject* MapReturn(const char* MapName);
	
protected:
	SkinModel		m_model;			//�X�L�����f��
	SkinModelData	m_modelData;		//�X�L�����f���f�[�^
	Light			m_light;			//���C�g
	D3DXVECTOR3		m_position;			//���W
	D3DXQUATERNION	m_rotation;			//��]
	D3DXVECTOR3		m_scale;			//�g��
	MeshCollider	m_meshCollider;		//���b�V���R���C�_�[
	RigidBody		m_rigidBody;		//���́B
	RigidBodyInfo	m_rbInfo;			//���̏��
};

