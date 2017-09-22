#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine\HID\Pad.h"
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
	void Draw();
	//�A�j���[�V��������
	void AnimationSet();
	//�ړ�����
	void move();
	//�ړ��L�[�̐ݒ�
	void Key();
	//�o���b�g�̓����菈��
	void BulletHit();

	//�v���C���[���W�̎擾
	D3DXVECTOR3 Getpos()
	{
		return characterController.GetPosition();
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
		//DamageTime = 200;
	}
private:
	enum PlayerState						//�v���C���[�A�j���[�V�����̏��
	{Stand, Move, Dash, Jump,Damage,Dead};
	bool				IsDead = false;		//���S�A�j���[�V�����t���O
	bool				Isrun=false;		//����A�j���[�V�����t���O
	bool				Ismove=false;		//���s�A�j���[�V�����t���O
	bool				Isjump=false;		//�W�����v�A�j���[�V�����t���O
	bool				Jumpflg = false;	//�W�����v�A�j���[�V�����t���O
	bool				IsDamage = false;	//�_���[�W�A�j���[�V�����t���O
	bool				IsStand = false;	//�ҋ@�A�j���[�V�����t���O
	//bool				IsAnimend = true;	//�A�j���[�V�����G���h�t���O
	bool				Damageflg = false;	//�_���[�W�A�j���[�V�����t���O
	int					DamageTime = 200;	//�_���[�W�Ԋu
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
	LPDIRECT3DTEXTURE9 normalMap = NULL;					//�@���}�b�v�B
	LPDIRECT3DTEXTURE9 specularMap = NULL;					//�X�y�L�����}�b�v�B

};

