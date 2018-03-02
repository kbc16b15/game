#pragma once
//#include "IGameObject.h"
//#include "HUD.h"
class PlayerHp :
	public IGameObject
{
public:
	//�R���X�g���N�^
	PlayerHp();
	~PlayerHp();

	void Init();
	void Update() {};
	void HudDraw();
	//�v���C���[�_���[�W����
	void PlayerDamage(int dame)
	{
		m_playerHpNum -= dame;
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
	int GetPlayerHpNum()
	{
		return m_playerHpNum;
	}
private:
	//�v���C���[HP
	D3DXVECTOR2	m_playerHpPos = { -550.0f,300.0f };	//�v���C���[HP���W
	const D3DXVECTOR2 m_playerHpScale = { 100.0f,100.0f };
	const int	m_playerHpMaxNum = 3;		//�ő�v���C���[HP��
	int			m_playerHpNum = 3;			//�v���C���[HP��
	const float	m_playerHpMovePos = 110.0f;	//�v���C���[HP�Ԋu
	Sprite		m_playerHpNo[3];			//�摜�\���̕ϐ�
	Texture		m_playerHpTexture;			//�X�v���C�g
};

