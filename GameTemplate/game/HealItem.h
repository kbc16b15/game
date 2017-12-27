#pragma once
#include "MapObject.h"
#include "Sound.h"
class HealItem :public MapObject
{
public:
	//�R���X�g���N�^
	HealItem();
	//�f�X�g���N�^
	~HealItem();
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

	bool GetHeal()
	{
		return m_healflg;
	}

private:
	SkinModel			m_model;							//�X�L�����f��
	SkinModelData		m_modelData;						//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position;					//���W
	D3DXQUATERNION		m_rotation;					//��]
	Light				m_light;							//���C�g
	MeshCollider		m_meshCollider;					//���b�V���R���C�_�[
	RigidBody			m_rigidBody;						//���́B
	RigidBodyInfo		m_rbInfo;							//���̏��
	bool				m_healflg = false;				//�񕜃A�C�e���̓���
	Sound*				m_healSound = nullptr;
};

