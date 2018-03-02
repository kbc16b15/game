#include "stdafx.h"
#include "BossHp.h"
#include "Fade.h"
//BossHp *BossHp::m_bossHp = NULL;

BossHp::BossHp()
{
}

BossHp::~BossHp()
{
	m_bossHpTexture.Release();
}

void BossHp::Init()
{
	m_bossHpTexture.Load("Assets/Sprite/hp3.png");
	//ボスのHP表示
	for (int i = 0;i <= m_bossHpMaxNum - 1;i++)
	{
		m_bossHpNo[i].Init(&m_bossHpTexture);
		m_bossHpNo[i].SetPosition(m_bossHpPos);
		m_bossHpNo[i].SetSize(m_bossHpScale);
		m_bossHpPos.x += m_bossHpMovePos;
	}

}

void BossHp::HudDraw()
{
	if (Fade::GetInstance().GetActive()) { return; }
	//ボスHPの描画
	for (int i = 0;i < m_bossHpNum;i++)
	{
		m_bossHpNo[i].Draw();
	}

}