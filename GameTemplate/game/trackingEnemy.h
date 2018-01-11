#pragma once

#include "myEngine/Physics/CharacterController.h"

class trackingEnemy
{
public:
	//�R���X�g���N�^
	trackingEnemy();
	//�f�X�g���N�^
	~trackingEnemy();
	//�������@���W�̐ݒ�
	void Start(D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//Enemy�̎��S����
	void Dead();
	//Enemy�̈ړ�����
	void Move();
	//Enemy�̎��S�t���O�̎擾
	bool GetDeathflg()
	{
		return m_isDeath;
	}

	/*D3DXMATRIX get()
	{
		return Transmat;
	}
	D3DXMATRIX rotget()
	{
		return rotmat;
	}

	bool Getparent()
	{
		return parent;
	}*/
	
private:
	enum TEnemyState
	{
		SEACH,
		FOUND,
		DEAD
	};
	/*D3DXMATRIX Transmat;
	D3DXMATRIX rotmat;*/
	//bool				parent = false;
	int TState = SEACH;
	SkinModel			m_skinModel;										//�X�L�����f��
	SkinModelData		m_skinModelData;									//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position;											//���W
	D3DXVECTOR3			m_sPos;												//�������W
	D3DXVECTOR3			m_scale = { 0.7f,0.7f,0.7f };						//�g��
	D3DXQUATERNION		m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);//��]
	Light				m_light;											//���C�g
	int					m_bulletTime = 150;									//�o���b�g�̔��ˊԊu
	bool				m_isDead = false;									//���S�����t���O
	bool				m_isDeath = false;									//���S�t���O
	int					m_deadTime = 100;									//���S�^�C��
	int					m_bulletDir = 0;									//�o���b�g�ł���
	CharacterController	m_characterController;								//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			m_moveSpeed = { 0.0f,0.0f,0.0f };					//�ړ����x
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;									//�@���}�b�v
	D3DXVECTOR3			m_direction = { 0.0f,0.0f,1.0f };
	bool				moveX = false;
	
};

