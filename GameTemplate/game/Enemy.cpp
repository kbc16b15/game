#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	m_skinModelData.Release();
}

void Enemy::Start(D3DXVECTOR3 pos)
{
	m_position = pos;
	m_skinModelData.LoadModelData("Assets/modelData/Enemy.X", NULL);
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

}

void Enemy::Update()
{
	EnemyBullet();
	Move();
	//scale.y -= 0.02f;
	CubeCollision Cmass;
	//position.y += 0.1f;
	if (Cmass.Cubemass(m_position, g_game->GetPlayer()->Getpos(),0.3f,0.3f))
	{
		g_game->GetPlayer()->SetJumpflg(true);
		m_isDead = true;
	}
	//position.y -= 0.1f;
	m_skinModel.UpdateWorldMatrix(m_position,D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0), m_scale);
	Dead();
}

void Enemy::Move()
{
	
	//if (IsDead) { return; }

	//if (position.y<2.0f)
	//{
	//	move =UP;
	//}
	//if (position.y>6.0f)
	//{
	//	move = DOWN;
	//}
}

void Enemy::EnemyBullet()
{
	D3DXVECTOR3 pos=g_game->GetPlayer()->Getpos();
	if (pos.x<m_position.x){ return; }//プレイヤーが左側にいる時だけ？
	if (m_isDead) { return; }
	
	m_bulletTime--;
	if (m_bulletTime < 0)
	{
		Bullet* bullet = new Bullet();
		bullet->Start(m_position, {10.0f,0.0f,0.0f},1);
		g_game->AddBullets(bullet);
		m_bulletTime = 150;
	}
}

void Enemy::Draw()
{
	m_skinModel.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());
}

void Enemy::Dead()
{
	if (!m_isDead) { return; }
	m_scale.y -= 0.01f;
	m_deadTime--;
	if (m_scale.y < 0.0f)
	{
		//characterController.RemoveRigidBoby();
		m_isDeath = true;
	}
	//IsDeath = true;
}