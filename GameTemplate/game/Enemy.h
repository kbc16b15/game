#pragma once

#include "myEngine/Physics/CharacterController.h"
//#include "IGameObject.h"

class Enemy/*:public IGameObject*/
{
public:
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();
	//�������@���W�̐ݒ�
	void Start(D3DXVECTOR3 pos);
	//�X�V
	void Update();
	//�G�l�~�[�̈ړ��̎d��
	void Move();
	//�`��
	void Draw();
	//Enemy�̃o���b�g�̔��˃^�C�~���O
	void EnemyBullet();
	//Enemy�̎��S����
	void Dead();
	//Enemy�̎��S�t���O�̎擾
	bool GetDeathflg()
	{
		return m_isDeath;
	}
private:
	SkinModel			m_skinModel;											//�X�L�����f��
	SkinModelData		m_skinModelData;										//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position = { -20.0f,0.0f,0.0f };					//���W
	D3DXVECTOR3			m_scale = { 0.5f,0.5f,0.5f };							//�g��
	D3DXQUATERNION		m_rotation= D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//��]
	Light				m_light;												//���C�g
	int					m_bulletTime = 150;									//�o���b�g�̔��ˊԊu
	bool				m_isDead = false;										//���S�����t���O
	bool				m_isDeath = false;									//���S�t���O
	int					m_deadTime = 100;										//���S�^�C��
	int					m_dulletDir = 0;										//�o���b�g�ł���
	CharacterController	m_characterController;				//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			m_moveSpeed = { 0.0f,0.0f,0.0f };		//�ړ����x
};

