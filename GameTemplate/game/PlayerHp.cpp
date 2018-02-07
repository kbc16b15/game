#include "stdafx.h"
#include "PlayerHp.h"

PlayerHp *PlayerHp::m_playerHp = NULL;
PlayerHp::PlayerHp()
{
}


PlayerHp::~PlayerHp()
{
}

void PlayerHp::Init()
{
	//�v���C���[��HP�\��
	for (int i = 0;i <= m_playerHpMaxNum - 1;i++)
	{
		m_playerHpNo[i].Initialize("Assets/Sprite/HP.png", m_playerHpPos);
		m_playerHpPos.x += m_playerHpMovePos;
	}
	//�X�v���C�g�̐���
	CreateSprite();
	//�v���C���[HP�̃A�b�v�f�[�g
	for (int i = 0;i < m_playerHpNum;i++)
	{
		m_playerHpNo[i].Update();
	}
}

void PlayerHp::Draw()
{
	//�v���C���[HP�̕`��
	for (int i = 0;i < m_playerHpNum;i++)
	{
		m_playerHpNo[i].Draw(m_sprite);
	}
}

HRESULT PlayerHp::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}
