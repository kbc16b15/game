#pragma once
#include "myEngine/Physics/CharacterController.h"
//#include "Particle.h"
#include "ParticleEmitter.h"
class BossEnemy:public IGameObject
{
public:

	~BossEnemy();
	void Release();
	//�������@���W�̐ݒ�
	void Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�J�n
	void Start();
	//Enemy�̎��S����
	void Dead();
	//�_���[�W
	void Damege();
	//�U��
	void Attack();
	//��]
	void rot();
	//Enemy�̈ړ�����
	void Stand();
	//Enemy�̎��S�t���O�̎擾
	bool GetDeathflg()
	{
		return m_isDeath;
	}
	//���W�̎擾
	D3DXVECTOR3 Getpos()
	{
		return m_characterController.GetPosition();
	}

	//�_���[�W�ʒm
	void SetDamage()
	{
		if (m_damageTime > 0) { return; }
		m_damageflg = true;
	}

	//�C���X�^���X�̐���
	static void BossEnemy::Create()
	{
		if (!m_bossEnemy)
		{
			m_bossEnemy = new BossEnemy;
		}

	}

	//�C���X�^���X�̏���
	static  void BossEnemy::Destroy()
	{
		delete m_bossEnemy;
		m_bossEnemy = nullptr;
	}
	//�C���X�^���X�̎擾
	static BossEnemy& GetInstance()
	{
		return *m_bossEnemy;
		
		
	}
private:
	BossEnemy();
	static BossEnemy* m_bossEnemy;
	enum BossEnemyState
	{
		START,
		STAND,
		ROT,
		ATTACK,
		DEAD
	};

	BossEnemyState BossState = START;
	SkinModel			m_skinModel;			//�X�L�����f��
	SkinModelData		m_skinModelData;		//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position;				//���W
	D3DXVECTOR3			m_sPos;					//�������W
	D3DXVECTOR3			m_targetPos;			//�ړI���W
	D3DXVECTOR3			m_scale;				//�g��
	D3DXQUATERNION		m_rotation;				//��]
	Light				m_light;				//���C�g
	int					m_bulletTime = 40;		//�o���b�g�̔��ˊԊu
	const int			m_bulletMaxTime = 40;	//�o���b�g�̍ő唭�ˊԊu
	bool				m_isDead = false;		//���S�����t���O
	bool				m_isDeath = false;		//���S�t���O
	int					m_deadTime = 500;		//���S�^�C��
	int					m_bulletDir = 0;		//�o���b�g�ł���
	CharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			m_moveSpeed;			//�ړ����x
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//�@���}�b�v
	D3DXVECTOR3			m_direction;			//����
	int					m_standTime = 120;		//�ҋ@�^�C��
	const int			m_maxStandTime=120;		//�ő�ҋ@�^�C��
	int					m_rotTime = 50;			//��]�^�C��
	const int			m_maxrotTime = 50;		//�ő��]�^�C��
	int					m_attackTime=80;		//�U���^�C��
	const int			m_maxAttackTime = 80;	//�ő�U���^�C��
	bool				m_moveX = false;		//�ړ��t���O
	bool				m_onTarget = false;		//�ڕW���W�����܂���
	float				m_targetlen=0.0f;		//�ڕW���W�Ƃ̋���
	float				m_stopAttackLen = 40.0f;//�ڕW���W�̋���
	int					m_startTime = 200;		//�J�n����
	int					m_damageTime = 0;		//���G����
	int					m_damageMaxTime = 200;	//�ő喳�G����
	bool				m_damageflg = false;	//�_���[�W�t���O
	ParticleEmitter		m_particleEmitter;	//�p�[�e�B�N��
	SParticleEmitParameter param;
};