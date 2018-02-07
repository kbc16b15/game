#include "stdafx.h"
#include "Spring.h"
#include "Player.h"

void Spring::Update()
{
	D3DXVECTOR3 toPos=m_position;
	toPos.y += 1.0f;
	D3DXVec3Subtract(&toPos, &m_position, &Player::GetInstance().Getpos());

	float len = D3DXVec3Length(&toPos);

	if (len <length)
	{
		Sflg = true;
		
	}
	else
	{
		/*Sflg = false;
		if (scale.y > 1.0f) { return; }
		scale.y += 0.03f;*/
	}

	if (Sflg)
	{
		/*D3DXVECTOR3 Ppos=Game::GetInstance().GetPlayer()->Getpos();
		Ppos.y = position.y + 2.0f;
		Game::GetInstance().GetPlayer()->Setpos({ position.x,position.y,position.z});
		Game::GetInstance().GetPlayer()->SetJumpflg(true);*///プレイヤーをジャンプさせる処理




		if (m_scale.y < 0.0f) 
		{
			m_maxDownflg = true;//ボタンを押し切った
			//delete this;
			return; 
		}
		m_scale.y -= 0.003f;
		m_position.y -= 0.01f;
	}
	m_model.UpdateWorldMatrix(m_position,m_rotation, m_scale);

}