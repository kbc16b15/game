#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "Sound.h"
class trackingEnemy
{
public:
	//�R���X�g���N�^
	trackingEnemy();
	//�f�X�g���N�^
	~trackingEnemy();
	//�������@���W�̐ݒ�
	void Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot);
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

private:
	enum TEnemyState
	{
		SEACH,
		FOUND,
		DEAD
	};

	int TState = SEACH;
	SkinModel			m_skinModel;			//�X�L�����f��
	SkinModelData		m_skinModelData;		//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position;				//���W
	D3DXVECTOR3			m_sPos;					//�������W
	D3DXVECTOR3			m_scale;				//�g��
	D3DXQUATERNION		m_rotation;				//��]
	Light				m_light;				//���C�g
	int					m_bulletTime = 60;		//�o���b�g�̔��ˊԊu
	bool				m_isDead = false;		//���S�����t���O
	bool				m_isDeath = false;		//���S�t���O
	int					m_deadTime = 100;		//���S�^�C��
	int					m_bulletDir = 0;		//�o���b�g�ł���
	CharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			m_moveSpeed;			//�ړ����x
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//�@���}�b�v
	D3DXVECTOR3			m_direction;//����
	bool				moveX = false;
	//Sound*				m_beamSound=nullptr;
	
};

