#include "stdafx.h"
#include "trackingEnemy.h"
#include "Enemy.h"
#include "Bullet.h"


trackingEnemy::trackingEnemy()
{
}

trackingEnemy::~trackingEnemy()
{
	m_characterController.RemoveRigidBoby();
	m_skinModelData.Release();

}

void trackingEnemy::Start(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	m_sPos = pos;
	m_position = pos;
	m_rotation = rot;
	m_skinModelData.LoadModelData("Assets/modelData/ghost.X", NULL);
	m_skinModel.Init(&m_skinModelData);

	//ライトを初期化。
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	m_skinModel.SetLight(&m_light);

	//キャラクタコントローラを初期化。
	m_characterController.Init(0.8f, 0.5f, m_position);
	m_characterController.SetGravity(-15.0f);

}

void trackingEnemy::Update()
{
	Move();
	Dead();

	if (m_moveSpeed.y > 0.0f)
	{
		m_moveSpeed.y = 0.0f;
	}
	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_moveSpeed);

	//キャラクタコントローラーを実行。
	m_characterController.Execute();

	m_skinModel.UpdateWorldMatrix(m_characterController.GetPosition(), m_rotation, m_scale);

}

void trackingEnemy::Move()
{
	//D3DXVECTOR3 Tpos = characterController.GetPosition();
	//エネミーの移動処理
	m_moveSpeed = m_characterController.GetMoveSpeed();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	D3DXVECTOR3 pos = g_game->GetPlayer()->Getpos();
	D3DXVECTOR3 toPos = pos - m_characterController.GetPosition();
	float len = D3DXVec3Length(&toPos);


	float angle = atan2f(m_direction.x, m_direction.z);
	D3DXVECTOR3 Def;
	D3DXVec3Subtract(&Def, &m_characterController.GetPosition(), &pos);

	float s;
	float halfAngle = /*angle*/atan2f(-Def.x, -Def.z) * 0.5f;
	switch (TState)
	{
	case SEACH:

		if (len < 6.0f)
		{
			TState = FOUND;
		}
		/*if (Tpos.x<-18.0f)
		{
			moveX = true;
		}
		else if(Tpos.x>3.0f)
		{
			moveX = false;
		}*/
		break;
	case FOUND:
		if (len > 10.0f)
		{
			TState = SEACH;
		}
		//position += toPos*0.05f;

		m_moveSpeed += toPos*1.5f;

		s = sin(halfAngle);
		m_rotation.w = cos(halfAngle);
		m_rotation.x = 0.0f * s;
		m_rotation.y = 1.0f * s;
		m_rotation.z = 0.0f * s;


		break;
	default:
		break;
	}
}

void trackingEnemy::Draw()
{
	m_skinModel.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());
}

void trackingEnemy::Dead()
{
	if (g_game->GetPlayer()->PlayerDeath())
	{
		m_isDeath = true;
	}
	/*D3DXVECTOR3 Ppos = characterController.GetPosition();
	if ((Spos.y-5.0f) >Ppos.y)
	{
		IsDeath = true;
	}*/
	CubeCollision Cmass;
	if (Cmass.Cubemass(m_characterController.GetPosition(), g_game->GetPlayer()->Getpos(), 0.5f, 0.5f))
	{
		g_game->GetPlayer()->SetDamage();
		m_isDeath = true;
	}

}