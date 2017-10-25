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
		return IsDeath;
	}
private:
	SkinModel			skinModel;											//�X�L�����f��
	SkinModelData		skinModelData;										//�X�L�����f���f�[�^
	D3DXVECTOR3			position = { -20.0f,0.0f,0.0f };					//���W
	D3DXVECTOR3			scale = { 0.5f,0.5f,0.5f };							//�g��
	D3DXQUATERNION		rotation= D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);	//��]
	Light				light;												//���C�g
	int					BulletTime = 150;									//�o���b�g�̔��ˊԊu
	bool				IsDead = false;										//���S�����t���O
	bool				IsDeath = false;									//���S�t���O
	int					DeadTime = 100;										//���S�^�C��
	int					BulletDir = 0;										//�o���b�g�ł���

};

