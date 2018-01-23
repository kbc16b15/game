#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy()
{
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = { 0.7f,0.7f,0.7f };
	m_direction = { 0.0f,0.0f,1.0f };
	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//m_beamSound = new Sound();
}

Enemy::~Enemy()
{
	m_skinModelData.Release();
	m_characterController.RemoveRigidBoby();
	if (m_normalMap != NULL)
	{
		m_normalMap->Release();
	}

	/*if (m_beamSound != nullptr)
	{
	delete m_beamSound;
	m_beamSound = nullptr;
	}*/
}

void Enemy::Init(D3DXVECTOR3 pos, D3DXQUATERNION	rot)
{
	m_sPos = pos;
	m_position = pos;
	m_rotation = rot;

	m_skinModelData.LoadModelData("Assets/modelData/Drone.X", NULL);

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
	m_characterController.SetGravity(0.0f);

	m_skinModel.SetSpecularlight(true);

	D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/PA_DroneNorm.png",
		&m_normalMap);

	if (m_normalMap != NULL)
	{
		m_skinModel.SetnormalMap(m_normalMap);
	}
}

void Enemy::Update()
{
	if (m_isDead) { return; }
	//m_beamSound->Update();

	Move();
	Dead();

	/*if (m_moveSpeed.y > 0.0f)
	{
		m_moveSpeed.y = 0.0f;
	}*/
	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_moveSpeed);

	//キャラクタコントローラーを実行。

	m_characterController.Execute();

	m_skinModel.UpdateWorldMatrix(m_characterController.GetPosition(), m_rotation, m_scale);

}

void Enemy::Move()
{
	//D3DXVECTOR3 Tpos = characterController.GetPosition();
	//エネミーの移動処理
	m_moveSpeed = m_characterController.GetMoveSpeed();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	D3DXVECTOR3 pos = g_game->GetPlayer()->Getpos();
	D3DXVECTOR3 toPos = pos - m_characterController.GetPosition();
	float len = D3DXVec3Length(&toPos);

	D3DXVECTOR3 tPos = pos - m_sPos;
	float Slen = D3DXVec3Length(&tPos);

	float angle = atan2f(m_direction.x, m_direction.z);
	D3DXVECTOR3 Def;
	D3DXVec3Subtract(&Def, &m_characterController.GetPosition(), &pos);

	float s;
	float halfAngle = /*angle*/atan2f(-Def.x, -Def.z) * 0.5f;
	switch (TState)
	{
	case SEACH:

		if (len < 8.0f)
		{
			TState = FOUND;
		}

		if (m_position.x>0.0f)
		{
			moveX = true;
		}
		else if (m_position.x<-40.0f)
		{
			moveX = false;
		}

		if (moveX)
		{
			//m_moveSpeed.x -= 5.5f;
		}
		else
		{
			//m_moveSpeed.x += 5.5f;
		}

		break;
	case FOUND:
		if (Slen > 10.0f)
		{
			TState = SEACH;
		}
		toPos.y = 0.0f;
		m_moveSpeed += toPos*1.0f;

		s = sin(halfAngle);
		m_rotation.w = cos(halfAngle);
		m_rotation.x = 0.0f * s;
		m_rotation.y = 1.0f * s;
		m_rotation.z = 0.0f * s;

		m_bulletTime--;
		if (m_bulletTime < 0)
		{
			Bullet* bullet = new Bullet();
			bullet->Start(m_characterController.GetPosition(),1);
			g_game->AddBullets(bullet);
			m_bulletTime = 60;

			Sound* m_beamSound = new Sound();
			m_beamSound->Init("Assets/Sound/beamgun.wav");
			m_beamSound->SetVolume(0.4f);
			m_beamSound->Play(false);
		}
		break;
	default:
		break;
	}
}

void Enemy::Draw()
{
	m_skinModel.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());
}

void Enemy::Dead()
{
	if (g_game->GetPlayer()->PlayerDeath())
	{
		m_isDeath = true;
	}
	//CubeCollision Cubemath;
	//if (Cmass.Cubemath(m_characterController.GetPosition(), g_game->GetPlayer()->Getpos(), 0.5f, 0.5f))
	//{
	//	g_game->GetPlayer()->SetDamage();
	////m_isDeath = true;
	//}

}