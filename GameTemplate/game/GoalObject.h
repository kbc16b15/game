#pragma once
#include "MapObject.h"
class GoalObject :public MapObject
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

private:
	SkinModel			m_model;			//�X�L�����f��
	SkinModelData		m_modelData;		//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position;			//���W
	D3DXQUATERNION		m_rotation;			//��]
	Light				m_light;			//���C�g
	MeshCollider		m_meshCollider;		//���b�V���R���C�_�[
	RigidBody			m_rigidBody;		//���́B
	RigidBodyInfo		m_rbInfo;			//���̏��
};

