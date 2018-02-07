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
	//プレイヤーのHP表示
	for (int i = 0;i <= m_playerHpMaxNum - 1;i++)
	{
		m_playerHpNo[i].Initialize("Assets/Sprite/HP.png", m_playerHpPos);
		m_playerHpPos.x += m_playerHpMovePos;
	}
	//スプライトの生成
	CreateSprite();
	//プレイヤーHPのアップデート
	for (int i = 0;i < m_playerHpNum;i++)
	{
		m_playerHpNo[i].Update();
	}
}

void PlayerHp::Draw()
{
	//プレイヤーHPの描画
	for (int i = 0;i < m_playerHpNum;i++)
	{
		m_playerHpNo[i].Draw(m_sprite);
	}
}

HRESULT PlayerHp::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}
