#include "stdafx.h"
#include "BossHp.h"

BossHp *BossHp::m_bossHp = NULL;

BossHp::BossHp()
{
}


BossHp::~BossHp()
{
}

void BossHp::Init()
{
	//ボスのHP表示
	for (int i = 0;i <= m_bossHpMaxNum - 1;i++)
	{
		m_bossHpNo[i].Initialize("Assets/Sprite/hp3.png", m_bossHpPos);
		m_bossHpPos.x += m_bossHpMovePos;
	}
	//スプライトの生成
	CreateSprite();

	//ボスHPのアップデート
	for (int i = 0;i < m_bossHpNum;i++)
	{
		m_bossHpNo[i].Update();
	}
}

void BossHp::Draw()
{
	//ボスHPの描画
	for (int i = 0;i < m_bossHpNum;i++)
	{
		m_bossHpNo[i].Draw(m_sprite);
	}

}

HRESULT BossHp::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}