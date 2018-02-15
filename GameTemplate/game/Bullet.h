#pragma once
class Bullet:public IGameObject
{
public:
	//�ł����L����
	enum CHARA {
		PLAYER,
		TANK,
		ENEMY
	};
	//�R���X�g���N�^
	Bullet();
	//�f�X�g���N�^
	~Bullet();
	//�������@���W�̐ݒ�
	void Init(D3DXVECTOR3 pos, float speed,CHARA chara);

	//�������@�ڕW���W�@���W�̐ݒ�
	void Start(D3DXVECTOR3 targetPos, D3DXVECTOR3 pos, float speed, CHARA chara);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�o���b�g�̎����ƒǏ]
	void TargetBullet();

	//�o���b�g�̓�����
	void BulletHit();

	//���S�t���O�̎擾
	bool GetDeathflg()
	{
		return m_bulletDeadflg;
	}
	//ID�̎擾
	CHARA GetID()
	{
		return m_chara;
	}

private:
	CHARA				m_chara;	//�e�̏��
	//CHARA				m_bulletId;			//�e��ID
	SkinModel			m_skinModel;		//�X�L�����f��
	static SkinModelData* m_skinModelData;	//�X�L�����f���f�[�^
	Light				m_light;			//���C�g
	D3DXVECTOR3			m_position;			//���W
	D3DXVECTOR3			m_scale;			//�g��
	D3DXQUATERNION		m_rotation;			//��]
	D3DXVECTOR3			m_targetPos;		//�ړI�̍��W
	D3DXVECTOR3			m_direction;		//�o���b�g�̌���
	int					m_btime = 300;		//�o���b�g�̎���
	const int			m_maxBtime = 300;	//�o���b�g�̍ő����
	bool				m_bulletDeadflg = false;	//�o���b�g�̎��S�t���O
	bool				m_find = false;		//�����t���O
	const float			m_bulletRadius=0.2f;//�o���b�g�̔��a
	const float			m_playerRadius=0.3f;//�v���C���[�̔��a
	float				m_bulletSpeed= 0.2f;//�o���b�g�̃X�s�[�h
	const float			m_playerUp = 0.3f;	//�v���C���[�̂����镝
	const float			m_bulletDeathlenge = 0.1f;//�o���b�g�����ʋ���
};

