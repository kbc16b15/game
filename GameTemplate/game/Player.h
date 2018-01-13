#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine\HID\Pad.h"
#include "Sound.h"
//#include "IGameObject.h"

class Player/*:public IGameObject*/
{
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//������
	void Start();
	//�X�V
	void Update();
	//�`��
	void Draw(D3DXMATRIX* viewM, D3DXMATRIX* projM,bool shadowCaster,bool shadowRecive);

	//�A�j���[�V��������
	void AnimationSet();
	//�ړ�����
	void move();
	//�ړ��L�[�̐ݒ�
	//void Key();
	//�o���b�g�̓����菈��
	void BulletHit();
	//�L�����̌����̐ݒ�
	void Setangle();

	//�v���C���[���W�̎擾
	D3DXVECTOR3 Getpos()
	{
		return m_characterController.GetPosition();
	}
	//���W�Z�b�g
	void Setpos(D3DXVECTOR3 pos)
	{
		m_position = pos;

	}
	//�v���C���[�̃W�����v�t���O�ݒ�
	void SetJumpflg(bool Jump)
	{
		m_jumpflg = Jump;
	}
	//�v���C���[�̈ړ����x��ݒ�
	void AddSpeed(D3DXVECTOR3 addpos)
	{
		m_characterController.SetMoveSpeed(addpos);
		m_characterController.Execute();
	}
	//�v���C���[�̈ړ����x�̎擾
	D3DXVECTOR3 GetSpeed()
	{
		return m_characterController.GetMoveSpeed();
	}
	//�_���[�W�ʒm
	void SetDamage()
	{
		if (m_damageTime > 0) { return; }
		m_damageflg = true;
	}

	//�ړ��̒�~
	void PlayerMoveSet(bool Move)
	{
		m_moveStop = Move;
	}
	//�v���C���[�̎��S�A�j���[�V�����̏I��
	bool PlayerDeath()
	{
		return m_deathflg;
	}
	//�I�u�W�F�N�g�Ƃ̓�����������
	bool GetObjectHit()
	{
		return m_objectHit;
	}

	//�I�u�W�F�N�g�Ƃ̓�����������̐ݒ�
	void SetObjectHit(bool hit)
	{
		m_objectHit = hit;
	}

	
private:
	enum PlayerState						//�v���C���[�A�j���[�V�����̏��
	{Stand, Move, Dash, Jump,Damage,Dead};
	PlayerState			m_state=Stand;
	PlayerState			m_workState = Stand;
	bool				m_isDead = false;		//���S�A�j���[�V�����t���O
	bool				m_isrun=false;			//����A�j���[�V�����t���O
	bool				m_ismove=false;			//���s�A�j���[�V�����t���O
	bool				m_isjump=false;			//�W�����v�A�j���[�V�����t���O
	bool				m_jumpflg = false;		//�W�����v�A�j���[�V�����t���O
	bool				m_isDamage = false;		//�_���[�W�A�j���[�V�����t���O
	bool				m_isStand = false;		//�ҋ@�A�j���[�V�����t���O
	bool				m_damageflg = false;	//�_���[�W�A�j���[�V�����t���O
	bool				m_deathflg = false;		//���S�t���O
	int					m_damageTime = 0;		//�_���[�W�Ԋu
	SkinModel			m_skinModel;							//�X�L�����f��
	SkinModelData		m_skinModelData;						//�X�L�����f���f�[�^
	Light				m_light;								//���C�g
	Animation			m_animation;							//�A�j���[�V����
	Pad					m_pad;									//�p�b�h
	CharacterController	m_characterController;					//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			m_position = { 0.0f,0.0f,0.0f };		//���W
	D3DXVECTOR3			m_scale = { 1.0f,1.0f,1.0f };			//�g��
	D3DXQUATERNION		m_rotation = { 0.0f,0.0f,0.0f,1.0f };	//��]
	D3DXVECTOR3			m_moveSpeed = { 0.0f,0.0f,0.0f };		//�ړ����x
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;						//�@���}�b�v
	LPDIRECT3DTEXTURE9	m_specularMap = NULL;					//�X�y�L�����}�b�v
	D3DXVECTOR3			m_dir = { 0.0f,0.0f,0.0f };				//���񂹁[
	D3DXVECTOR3			m_Addvector = { 0.0f,0.0f,0.0f };		//���Z���x
	//Sound*				m_JumpSound = nullptr;					//�W�����v��
	float				m_Gravity = -10.0f;						//�d��
	const float			m_maxSpeed=5.0f;						//�ő�ړ����x�̕ۑ�
	const float			m_jumpHeight = 8.0f;					//�W�����v�̍���
	const float			m_downSpeed = 0.3f;						//�ړ����Ă��Ȃ��Ƃ��Ɍ��������鏈��(���C�H)
	bool				m_moveStop = false;
	bool				m_objectHit = false;
	bool				m_maxSflg = false;


};