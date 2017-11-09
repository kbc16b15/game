#pragma once
//#include "IGameObject.h"
class Bullet/*:public IGameObject*/
{
public:
	//�R���X�g���N�^
	Bullet();
	//�f�X�g���N�^
	~Bullet();
	//�������@���W�̐ݒ�
	void Start(D3DXVECTOR3 pos,D3DXVECTOR3 targetPos,int cha);
	//�X�V
	void Update();
	//�`��
	void Draw();

	//���W�擾
	D3DXVECTOR3 Getpos()
	{
		return position;
	}
	//�o���b�g�̎����ƒǏ]
	void TargetBullet();

	//���S�t���O�̎擾
	bool GetBulletflg()
	{
		return Bulletflg;
	}
	//�ł����L����
	enum Chara {
		Player,
		Enemy
	};
private:
	//enum EState {
	//	eState_Search,	//���G��ԁB
	//	eState_Find,	//������ԁB
	//};
	//EState state;		//�G�̏�ԁB

	int m_Chara = Enemy;//�e�̏��
	SkinModel			skinModel;										//�X�L�����f��
	static SkinModelData* skinModelData;								//�X�L�����f���f�[�^
	Light				light;											//���C�g
	D3DXVECTOR3			position = { 0.0f,0.0f,0.0f };					//���W
	D3DXVECTOR3			scale = { 0.3f,0.3f,0.3f };						//�g��
	D3DXQUATERNION		rotation=D3DXQUATERNION(0.0f, 1.0f, 0.0f, 1.0);	//��]
	D3DXVECTOR3			Playerpos;										//�v���C���[�̍��W�̊i�[�ϐ�
	D3DXVECTOR3			TargetPos;										//�ړI�̍��W
	D3DXVECTOR3			direction;										//�o���b�g�̌���
	int					Btime = 300;									//�o���b�g�̎���
	bool				Bulletflg = true;								//�o���b�g�̎��S�t���O
	bool				Find = false;									//�����t���O
};

