#pragma once
#include "IGameObject.h"
class BossHp :
	public IGameObject
{
public:
	//�R���X�g���N�^
	BossHp();
	//�f�X�g���N�^
	~BossHp();

	void Init();
	void Update() {};
	void HudDraw();

	//�{�X�_���[�W����
	void BossDamage(int dame)
	{
		m_bossHpNum -= dame;
	}
	//�{�XHP�̎擾
	int GetBossHpNum()
	{
		return m_bossHpNum;
	}
	////�C���X�^���X�̐���
	//static void Create()
	//{
	//	if (!m_bossHp)
	//	{
	//		m_bossHp = new BossHp;
	//	}

	//}

	////�C���X�^���X�̏���
	//static void Destroy()
	//{
	//	delete m_bossHp;
	//	m_bossHp = nullptr;
	//}
	////�C���X�^���X�̎擾
	//static BossHp& GetInstance()
	//{
	//	return *m_bossHp;
	//}
private:
	//static BossHp* m_bossHp;//�C���X�^���X
private:

	//�{�XHP
	D3DXVECTOR2			m_bossHpPos = { 140.0f,-300.0f };	//�{�X��HP���W
	const D3DXVECTOR2	m_bossHpScale = { 100.0f,100.0f };
	const int			m_bossHpMaxNum = 5;			//�{�X�̍ő�HP
	int					m_bossHpNum = 5;			//�{�X��HP
	const float			m_bossHpMovePos = 100.0f;	//�{�X��HP�Ԋu
	Sprite				m_bossHpNo[5];				//�摜�\���̕ϐ�
	Texture				m_bossHpTexture;					//�e�N�X�`��
};

