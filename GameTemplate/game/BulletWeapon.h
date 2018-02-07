#pragma once
#include "IGameObject.h"
#include "myEngine/Physics/CharacterController.h"

class BulletWeapon :
	public IGameObject
{
public:
	//�R���X�g���N�^
	BulletWeapon();
	//�f�X�g���N�^
	~BulletWeapon();
	//�������@���W�̐ݒ�
	void Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//	BulletWeapon�̎��S����
	void Dead();
	//	BulletWeapon�̈ړ�����
	void Move();
	//	BulletWeapon�̎��S�t���O�̎擾
	bool GetDeathflg()
	{
		return m_isDeath;
	}

private:
	enum BulletWeaponState
	{
		STAND,
		BULLET,
		DEAD
	};

	BulletWeaponState	m_bulletWeaponState = STAND;//�G�̏��
	SkinModel			m_skinModel;			//�X�L�����f��
	SkinModelData		m_skinModelData;		//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position;				//���W
	D3DXVECTOR3			m_scale;				//�g��
	D3DXQUATERNION		m_rotation;				//��]
	Light				m_light;				//���C�g
	int					m_bulletIntervalTime = 20;	//�o���b�g�̔��ˊԊu
	bool				m_isDead = false;		//���S�����t���O
	bool				m_isDeath = false;		//���S�t���O
	bool				m_isPlayerBulletCamera = false;//�o���b�g�J����
	bool				m_isPlayerBullet = false;
	int					m_deadTime = 100;		//���S�^�C��
	int					m_bulletDir = 0;		//�o���b�g�ł���
	//CharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			m_moveSpeed;			//�ړ����x
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//�@���}�b�v
	D3DXVECTOR3			m_direction;			//����
	const float			m_enemySpeed = 1.2f;	//�G�̑��x
	const float			m_playerBulletLenge = 2.0f;	//�o���b�g���łĂ鋗��
	const float			m_standLenge = 2.0f;	//����
	const float			m_charaRadius = 0.5f;	//�L�����̔��a
	const float			m_charaHeight = 0.5f;	//�L�����̍���
	const float			m_beamVolume = 0.4f;	//�r�[������
	const int			m_maxBulletTime = 60;	//�ő厀�S�^�C��


};

