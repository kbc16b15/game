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
		return m_position;
	}

	enum DamageObjectType {
		STAND,
		ROT,
		MOVE,
	};
private:
	int				m_damageType = STAND;
	SkinModel		m_model;					//�X�L�����f��
	SkinModelData	m_modelData;				//�X�L�����f���f�[�^
	D3DXVECTOR3		m_position;					//���W
	D3DXQUATERNION	m_rotation;					//��]
	D3DXVECTOR3		m_scale;					//�g��
	Light			m_light;					//���C�g
	MeshCollider	m_meshCollider;			//���b�V���R���C�_�[
	RigidBody		m_rigidBody;				//���́B
	RigidBodyInfo	m_rbInfo;					//���̏��
	D3DXVECTOR3		m_rotDir;					//��]����
	D3DXVECTOR3		m_totSpeed;				//��]���x
	float			m_angle = 0.0f;			//�p�x
	bool			m_rotflg = false;
};