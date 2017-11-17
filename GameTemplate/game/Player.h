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
		return characterController.GetPosition();
	}
	//���W�Z�b�g
	void Setpos(D3DXVECTOR3 pos)
	{
		position = pos;

	}
	//�v���C���[�̃W�����v�t���O�ݒ�
	void SetJumpflg(bool Jump)
	{
		Jumpflg = Jump;
	}
	//�v���C���[�̈ړ����x��ݒ�
	void AddSpeed(D3DXVECTOR3 addpos)
	{
		characterController.SetMoveSpeed(addpos);
		characterController.Execute();
	}
	//�v���C���[�̈ړ����x�̎擾
	D3DXVECTOR3 GetSpeed()
	{
		return characterController.GetMoveSpeed();
	}
	//�_���[�W�ʒm
	void SetDamage()
	{
		if (DamageTime > 0) { return; }
		Damageflg = true;
	}

	//�ړ��̒�~
	void PlayerMoveSet(bool Move)
	{
		MoveStop = Move;
	}
	//�v���C���[�̎��S�A�j���[�V�����̏I��
	bool PlayerDeath()
	{
		return Deathflg;
	}
	//�I�u�W�F�N�g�Ƃ̓�����������
	bool GetObjectHit()
	{
		return ObjectHit;
	}

	//�I�u�W�F�N�g�Ƃ̓�����������̐ݒ�
	void SetObjectHit(bool hit)
	{
		ObjectHit = hit;
	}

	////�d�͂̐ݒ�
	//void SetGravity()
	//{
	//	if (m_isGravity)
	//	{
	//		characterController.SetGravity(-10.0f);
	//		m_isGravity = false;
	//	}
	//	else
	//	{
	//		characterController.SetGravity(10.0f);
	//		m_isGravity = true;
	//	}
	//	
	//}
private:
	enum PlayerState						//�v���C���[�A�j���[�V�����̏��
	{Stand, Move, Dash, Jump,Damage,Dead};
	PlayerState			m_State=Stand;
	PlayerState			workState = Stand;
	bool				IsDead = false;		//���S�A�j���[�V�����t���O
	bool				Isrun=false;		//����A�j���[�V�����t���O
	bool				Ismove=false;		//���s�A�j���[�V�����t���O
	bool				Isjump=false;		//�W�����v�A�j���[�V�����t���O
	bool				Jumpflg = false;	//�W�����v�A�j���[�V�����t���O
	bool				IsDamage = false;	//�_���[�W�A�j���[�V�����t���O
	bool				IsStand = false;	//�ҋ@�A�j���[�V�����t���O
	bool				Damageflg = false;	//�_���[�W�A�j���[�V�����t���O
	bool				Deathflg = false;	//���S�t���O
	int					DamageTime = 0;		//�_���[�W�Ԋu
	SkinModel			skinModel;							//�X�L�����f��
	SkinModelData		skinModelData;						//�X�L�����f���f�[�^
	Light				light;								//���C�g
	Animation			animation;							//�A�j���[�V����
	D3DXVECTOR3			position = { 0.0f,0.0f,0.0f };		//���W
	D3DXVECTOR3			scale = { 1.0f,1.0f,1.0f };			//�g��
	D3DXQUATERNION		rotation = { 0.0f,0.0f,0.0f,1.0f };	//��]
	CharacterController	characterController;				//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			moveSpeed = { 0.0f,0.0f,0.0f };		//�ړ����x
	Pad					pad;								//�p�b�h
	LPDIRECT3DTEXTURE9	normalMap = NULL;					//�@���}�b�v
	LPDIRECT3DTEXTURE9	specularMap = NULL;					//�X�y�L�����}�b�v
	D3DXVECTOR3			Addvector = { 0.0f,0.0f,0.0f };		//���Z���x
	float				m_Gravity = -10.0f;					//�d��
	//bool				m_isGravity = false;				//���]�t���O
	//float				gAngle = 0.0f;
	//bool				Grotflg = true;
	bool				MoveStop = false;
	bool				ObjectHit = false;
	bool				maxSflg = false;
	D3DXVECTOR3 Dir = { 0.0f,0.0f,0.0f };//���񂹁[
	
	Sound*				m_JumpSound = nullptr;

};

//extern Player*		g_player;
