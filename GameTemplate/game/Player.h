#pragma once
#include "myEngine/Physics/CharacterController.h"
#include "Sound.h"
class Player:public IGameObject
{
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void ShadowDraw(D3DXMATRIX* viewM, D3DXMATRIX* projM, bool shadowCaster, bool shadowRecive);
	//�`��
	void Draw();
	//�T�E���h
	void PlayerSound();
	//�A�j���[�V��������
	void AnimationSet();
	//�ړ�����
	void move();
	//�ړ��L�[�̐ݒ�
	//void Key();
	//�o���b�g�̓����菈��
	void Hit();
	//�L�����̌����̐ݒ�
	void Setangle();
	//�L�����̃W�����v�̐ݒ�
	void Setjump();
	//�L�����̊����̐ݒ�
	void SetSubmove();

	void PlayerBullet();
	//�v���C���[���W�̎擾�i�����H�j
	const D3DXVECTOR3 Getpos()
	{
		return m_characterController.GetPosition();
	}
	//�v���C���[���S���W�̎擾
	const D3DXVECTOR3 GetMiddlepos()
	{
		return m_middlePosition;
	}
	//���W�Z�b�g
	void Setpos(D3DXVECTOR3 pos)
	{
		m_characterController.SetPosition(pos);

	}
	//�v���C���[�̈ړ����x��ݒ�
	void AddSpeed(D3DXVECTOR3 addpos)
	{
		m_characterController.SetMoveSpeed(addpos);
		m_characterController.Execute();

	}
	//�v���C���[�̈ړ�������ݒ�
	void SetDir(int dir)
	{
		m_addDir = dir;
	}
	//�v���C���[�̈ړ��������擾
	int GetDir()
	{
		return m_addDir;
	}
	//�v���C���[�̈ړ����x�̎擾
	const D3DXVECTOR3 GetSpeed()
	{
		return m_characterController.GetMoveSpeed();
	}
	//�_���[�W�ʒm
	void SetDamage()
	{
		if (m_damageTime > 0) { return; }
		m_isDamageflg = true;
	}

	

	//�ړ����Ă��邩�̎擾
	const bool GetPlayerMove()
	{
		return m_ismove;
	}
	//�v���C���[�̎��S�A�j���[�V�����̏I��
	bool GetPlayerDeath()
	{
		return m_isDeathflg;
	}
	void SetDeath(bool isdeath)
	{
		m_isDeathflg = isdeath;
	}
	//�v���C���[���n�ʂɂ��Ă��邩�ǂ���
	const bool GetGround()
	{
		return m_characterController.IsOnGround();
	}

	//�C���X�^���X�̐���
	static void Player::Create()
	{
		if (!player)
		{
			player = new Player;
		}

	}

	//�C���X�^���X�̏���
	static void Player::Destroy()
	{
		delete player;
		player = nullptr;
	}
	//�C���X�^���X�̎擾
	static Player& GetInstance()
	{
		return *player;
	}
	//�X�L�����f���̎擾
	SkinModel* GetSkinModel()
	{
		return &m_skinModel;
	}
	void SetMove(bool isMove)
	{
		m_isMoveStop = isMove;
	}
private:

	static Player* player;//�C���X�^���X
	enum PlayerState							//�v���C���[�A�j���[�V�����̏��
	{Stand, Dash, Jump,Damage,Dead,Bullets};
	PlayerState			m_state=Stand;
	PlayerState			m_workState = Stand;
	bool				m_isDead = false;		//���S�A�j���[�V�����t���O
	bool				m_isrun=false;			//����A�j���[�V�����t���O
	bool				m_ismove=false;			//���s�A�j���[�V�����t���O
	bool				m_isjump=false;			//�W�����v�A�j���[�V�����t���O
	bool				m_jumpflg = false;		//�W�����v�A�j���[�V�����t���O
	bool				m_isDamage = false;		//�_���[�W�A�j���[�V�����t���O
	bool				m_isStand = false;		//�ҋ@�A�j���[�V�����t���O
	bool				m_isDamageflg = false;	//�_���[�W�A�j���[�V�����t���O
	bool				m_isDeathflg = false;		//���S�t���O
	bool				m_isBulletflg = false;
	int					m_damageTime = 0;		//���G����
	int					m_damageMaxTime = 200;	//�ő喳�G����
	SkinModel			m_skinModel;			//�X�L�����f��
	SkinModelData		m_skinModelData;		//�X�L�����f���f�[�^
	Light				m_light;				//���C�g
	Animation			m_animation;			//�A�j���[�V����
	CharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			m_position;				//���W
	D3DXVECTOR3			m_middlePosition;		//�v���C���[�̒��S���W
	D3DXVECTOR3			m_scale;				//�g��
	D3DXQUATERNION		m_rotation;				//��]
	const float			m_charaRadius=0.6f;		//�L�����̔��a
	const float			m_charaHeight=0.5f;		//�L�����̍���
	D3DXVECTOR3			m_moveSpeed ;			//�ړ����x
	D3DXVECTOR3			m_dir;					//���񂹁[
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//�@���}�b�v
	LPDIRECT3DTEXTURE9	m_specularMap = NULL;	//�X�y�L�����}�b�v
	//LPDIRECT3DTEXTURE9	m_normalMapGun = NULL;		//�@���}�b�v
	//LPDIRECT3DTEXTURE9	m_specularMapGun = NULL;	//�X�y�L�����}�b�v
	float				m_gravity = -10.0f;		//�d��
	bool				m_isMoveStop = false;		//�ړ��Ɖ�]���Ȃ���
	bool				m_isMax = false;		//�ő�ړ����x�̃t���O
	//bool				m_isGaraviey = true;
	int					m_addDir = 0;			//���Z����
	D3DXVECTOR3			m_cameraTar;
	D3DXVECTOR3			m_cameraPos;

	const float			m_playerBulletLenge = 2.0f;	//�o���b�g���łĂ鋗��
	const float			m_beamVolume = 0.4f;	//�r�[������
	const int			m_maxBulletTime = 60;	//�ő厀�S�^�C��

	int					m_bulletIntervalTime = 20;	//�o���b�g�̔��ˊԊu
	//bool				m_isDead = false;		//���S�����t���O
	//bool				m_isDeath = false;		//���S�t���O
	bool				m_isPlayerBulletCamera = false;//�o���b�g�J����
	bool				m_isPlayerBullet = false;
	Sound*				m_jumpSound=nullptr;
	Sound*				m_beamSound=nullptr;
};