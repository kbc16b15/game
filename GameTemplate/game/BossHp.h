#pragma once
#include "IGameObject.h"
#include "HUD.h"
class BossHp :
	public IGameObject
{
public:
	//BossHp();
	~BossHp();

	void Init();
	void Update() {};
	void Draw();

	//�X�v���C�g�����֐�
	HRESULT CreateSprite();
	//�{�X�_���[�W����
	void BossDamage(int dame)
	{
		m_bossHpNum -= dame;
		//�{�XHP�̃A�b�v�f�[�g
		for (int i = 0;i < m_bossHpNum;i++)
		{
			m_bossHpNo[i].Update();
		}
	}
	//�{�XHP�̎擾
	int GetBossHp()
	{
		return m_bossHpNum;
	}
	//�C���X�^���X�̐���
	static void BossHp::Create()
	{
		if (!m_bossHp)
		{
			m_bossHp = new BossHp;
		}

	}

	//�C���X�^���X�̏���
	static  void BossHp::Destroy()
	{
		delete m_bossHp;
		m_bossHp = nullptr;
	}
	//�C���X�^���X�̎擾
	static BossHp& GetInstance()
	{
		return *m_bossHp;
	}
private:
	//�R���X�g���N�^
	BossHp();
	static BossHp* m_bossHp;//�C���X�^���X
private:

	//�{�XHP
	D3DXVECTOR2			m_bossHpPos = { 800.0f,620.0f };	//�{�X��HP���W
	const int			m_bossHpMaxNum = 5;			//�{�X�̍ő�HP
	int					m_bossHpNum = 5;			//�{�X��HP
	const float			m_bossHpMovePos = 100.0f;	//�{�X��HP�Ԋu
	HUD					m_bossHpNo[5];				//�摜�\���̕ϐ�
	LPD3DXSPRITE		m_sprite;					//�X�v���C�g
};

