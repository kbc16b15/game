#pragma once
//#include "IGameObject.h"
#include "HUD.h"
class PlayerHp :
	public IGameObject
{
public:
	//PlayerHp();
	~PlayerHp();

	void Init();
	void Update() {};
	void Draw();
	//�X�v���C�g�����֐�
	HRESULT CreateSprite();

	//�v���C���[�_���[�W����
	void PlayerDamage(int dame)
	{
		m_playerHpNum -= dame;
		//�v���C���[HP�̃A�b�v�f�[�g
		for (int i = 0;i < m_playerHpNum;i++)
		{
			m_playerHpNo[i].Update();
		}
	}
	//�v���C���[�̗͂̉�
	void PlayerHeal(int healval)
	{
		m_playerHpNum += healval;
		if (m_playerHpNum >= m_playerHpMaxNum)
		{
			m_playerHpNum = m_playerHpMaxNum;
		}
	}
	//�v���C���[HP�̎擾
	int GetPlayerHp()
	{
		return m_playerHpNum;
	}

	//�C���X�^���X�̐���
	static void PlayerHp::Create()
	{
		if (!m_playerHp)
		{
			m_playerHp = new PlayerHp;
		}

	}

	//�C���X�^���X�̏���
	static  void PlayerHp::Destroy()
	{
		delete m_playerHp;
		m_playerHp = nullptr;
	}
	//�C���X�^���X�̎擾
	static PlayerHp& GetInstance()
	{
		return *m_playerHp;
	}
private:
	//�R���X�g���N�^
	PlayerHp();
	static PlayerHp* m_playerHp;//�C���X�^���X
private:
	//�v���C���[HP
	D3DXVECTOR2			m_playerHpPos = { 120.0f,80.0f };	//�v���C���[HP���W
	const int			m_playerHpMaxNum = 3;		//�ő�v���C���[HP��
	int					m_playerHpNum = 3;			//�v���C���[HP��
	const float			m_playerHpMovePos = 100.0f;	//�v���C���[HP�Ԋu
	HUD					m_playerHpNo[3];				//�摜�\���̕ϐ�
	LPD3DXSPRITE		m_sprite;					//�X�v���C�g
};

