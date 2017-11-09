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
	void Start(D3DXVECTOR3 pos);
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
		return IsDeath;
	}
	enum TEnemyState
	{
		SEACH,
		FOUND,
		DEAD

	};
private:
	int TState = SEACH;
	SkinModel			skinModel;											//�X�L�����f��
	SkinModelData		skinModelData;										//�X�L�����f���f�[�^
	D3DXVECTOR3			position;											//���W
	D3DXVECTOR3			Spos;												//�������W
	D3DXVECTOR3			scale = { 1.0f,1.0f,1.0f };							//�g��
	D3DXQUATERNION		rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//��]
	Light				light;												//���C�g
	int					BulletTime = 150;									//�o���b�g�̔��ˊԊu
	bool				IsDead = false;										//���S�����t���O
	bool				IsDeath = false;									//���S�t���O
	int					DeadTime = 100;										//���S�^�C��
	int					BulletDir = 0;										//�o���b�g�ł���
	CharacterController	characterController;				//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			moveSpeed = { 0.0f,0.0f,0.0f };		//�ړ����x

	D3DXVECTOR3 direction = { 0.0f,0.0f,1.0f };
	bool				moveX = false;

};

