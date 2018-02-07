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
	//�{�X��HP�\��
	for (int i = 0;i <= m_bossHpMaxNum - 1;i++)
	{
		m_bossHpNo[i].Initialize("Assets/Sprite/hp3.png", m_bossHpPos);
		m_bossHpPos.x += m_bossHpMovePos;
	}
	//�X�v���C�g�̐���
	CreateSprite();

	//�{�XHP�̃A�b�v�f�[�g
	for (int i = 0;i < m_bossHpNum;i++)
	{
		m_bossHpNo[i].Update();
	}
}

void BossHp::Draw()
{
	//�{�XHP�̕`��
	for (int i = 0;i < m_bossHpNum;i++)
	{
		m_bossHpNo[i].Draw(m_sprite);
	}

}

HRESULT BossHp::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}