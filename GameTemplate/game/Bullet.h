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
		return m_position;
	}
	//�o���b�g�̎����ƒǏ]
	void TargetBullet();

	//���S�t���O�̎擾
	bool GetBulletflg()
	{
		return m_bulletflg;
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

	int					m_Chara = Enemy;//�e�̏��
	SkinModel			m_skinModel;										//�X�L�����f��
	static SkinModelData* m_skinModelData;									//�X�L�����f���f�[�^
	Light				m_light;											//���C�g
	D3DXVECTOR3			m_position = { 0.0f,0.0f,0.0f };					//���W
	D3DXVECTOR3			m_scale = { 0.3f,0.3f,0.3f };						//�g��
	D3DXQUATERNION		m_rotation=D3DXQUATERNION(0.0f, 1.0f, 0.0f, 1.0);	//��]
	D3DXVECTOR3			m_playerpos;										//�v���C���[�̍��W�̊i�[�ϐ�
	D3DXVECTOR3			m_targetPos;										//�ړI�̍��W
	D3DXVECTOR3			m_direction;										//�o���b�g�̌���
	int					m_btime = 300;									//�o���b�g�̎���
	bool				m_bulletflg = true;								//�o���b�g�̎��S�t���O
	bool				m_find = false;									//�����t���O
};

