#pragma once
#include "myEngine/Physics/CharacterController.h"
#include "ParticleEmitter.h"
class BossEnemy:public IGameObject
{
public:

	~BossEnemy();
	//�������@���W�̐ݒ�
	void Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot);
	//�X�V
	void Update();
	//�`��
	void HudDraw();
	//�`��
	void Draw();
	//�J�n
	void StartState();
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
		m_isDamageflg = true;
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

	BossEnemyState		m_bossState = START;
	SkinModel			m_skinModel;			//�X�L�����f��
	SkinModelData		m_skinModelData;		//�X�L�����f���f�[�^
	D3DXVECTOR3			m_position;				//���W
	D3DXVECTOR3			m_middlePosition;		//�{�X�̒��S���W
	D3DXVECTOR3			m_sPos;					//�������W
	D3DXVECTOR3			m_targetPos;			//�ړI���W
	D3DXVECTOR3			m_scale;				//�g��
	D3DXQUATERNION		m_rotation;				//��]
	Light				m_light;				//���C�g
	const float			m_charaRadius = 2.5f;	//�L�����̔��a
	int					m_bulletTime = 10;		//�o���b�g�̔��ˊԊu
	const int			m_bulletMaxTime = 10;	//�o���b�g�̍ő唭�ˊԊu
	//bool				m_isDead = false;		//���S�����t���O
	bool				m_isDeath = false;		//���S�t���O
	int					m_deadTime = 500;		//���S�^�C��
	int					m_bulletDir = 0;		//�o���b�g�ł���
	CharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	D3DXVECTOR3			m_moveSpeed;			//�ړ����x
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;		//�@���}�b�v
	LPDIRECT3DTEXTURE9	m_specularMap = NULL;	//�X�y�L�����}�b�v
	D3DXVECTOR3			m_direction;			//����
	int					m_standTime = 120;		//�ҋ@�^�C��
	const int			m_maxStandTime=120;		//�ő�ҋ@�^�C��
	int					m_rotTime = 50;			//��]�^�C��
	const int			m_maxrotTime = 50;		//�ő��]�^�C��
	int					m_attackTime=80;		//�U���^�C��
	const int			m_maxAttackTime = 80;	//�ő�U���^�C��
	bool				m_isTarget = false;		//�ڕW���W�����܂���
	float				m_targetLen=0.0f;		//�ڕW���W�Ƃ̋���
	float				m_stopAttackLen = 40.0f;//�ڕW���W�̋���
	int					m_startTime = 200;		//�J�n����
	int					m_damageTime = 0;		//���G����
	int					m_damageMaxTime = 200;	//�ő喳�G����
	bool				m_isDamageflg = false;	//�_���[�W�t���O
	bool				m_isAddParticle=false;	//�p�[�e�B�N���t���O
	float				m_soundBreakTime = 0.6f;//���j�T�E���h�̊Ԋu
	const float			m_soundBreakMaxTime = 0.6f;//���j�T�E���h�̍ő�Ԋu
	ParticleEmitter*	m_particleEmitter;	//�p�[�e�B�N��
};