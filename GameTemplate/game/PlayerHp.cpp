#include "stdafx.h"
#include "PlayerHp.h"
#include "Fade.h"
//PlayerHp *PlayerHp::m_playerHp = NULL;
PlayerHp::PlayerHp()
{

}

PlayerHp::~PlayerHp()
{
	m_playerHpTexture.Release();
}

void PlayerHp::Init()
{
	m_playerHpTexture.Load("Assets/Sprite/HP.png");
	//�v���C���[��HP�\��
	for (int i = 0;i <= m_playerHpMaxNum - 1;i++)
	{

		m_playerHpNo[i].Init(&m_playerHpTexture);
		m_playerHpNo[i].SetPosition(m_playerHpPos);
		m_playerHpNo[i].SetSize(m_playerHpScale);
		m_playerHpPos.x += m_playerHpMovePos;
	}
}

void PlayerHp::HudDraw()
{
	if (Fade::GetInstance().GetActive()) { return; }
	//�v���C���[HP�̕`��
	for (int i = 0;i < m_playerHpNum;i++)
	{
		m_playerHpNo[i].Draw();
	}
}