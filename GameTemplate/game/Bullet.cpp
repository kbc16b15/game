#include "stdafx.h"
#include "Bullet.h"
#include "BossEnemy.h"
#include "Player.h"
#include "EnemyManager.h"

SkinModelData* Bullet::m_skinModelData = NULL;

Bullet::Bullet()
{
	m_rotation = D3DXQUATERNION(0.0f, 1.0f, 0.0f, 1.0);	//回転
	m_scale = { 0.5f,0.5f,0.5f };						//拡大
	m_position = { 0.0f,0.0f,0.0f };					//座標
}

Bullet::~Bullet()
{
	delete m_skinModelData;
	m_skinModelData = NULL;
}

void Bullet::Start(D3DXVECTOR3 targetpos,D3DXVECTOR3 pos, float speed, CHARA chara)
{
	//ライトを初期化。
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(20.0f, 20.0f, 1.0f, 1.0f));

	if (m_skinModelData == NULL) {
		//モデルをロード。

		m_skinModelData = new SkinModelData;
		m_skinModelData->LoadModelData("Assets/modelData/Bullet.X", NULL);
	}
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetLight(&m_light);
	m_direction = { 0.0f, 0.0f, 1.0f };

	m_chara = chara;
	m_position = pos;
	m_bulletSpeed = speed;
	m_targetPos = targetpos;


	D3DXVECTOR3 toPos = m_targetPos - m_position;
	float len = D3DXVec3Length(&toPos);

	float angle = atan2f(m_direction.x, m_direction.z);
	D3DXVECTOR3 Def;
	D3DXVec3Subtract(&Def, &m_position, &m_targetPos);
	float s;
	float halfAngle = /*angle*/atan2f(-Def.x, -Def.z) * 0.5f;

	s = sin(halfAngle);
	m_rotation.w = cos(halfAngle);
	m_rotation.x = 0.0f * s;
	m_rotation.y = 1.0f * s;
	m_rotation.z = 0.0f * s;

	m_breakSound = new Sound;
}

void Bullet::Update()
{
	if (m_bulletDeadflg) { return; };
	BulletHit();
	TargetBullet();
	if (m_breakSound != nullptr) {
		if (m_breakSound->IsPlaying())
			m_breakSound->Update();
	}
	//skinModel.UpdateWorldMatrix(position,rotation, scale);

}

void Bullet::TargetBullet()
{

	//追従バレット
	/*	D3DXVECTOR3 toPos = targetpos - position;
		D3DXVec3Normalize(&toPos, &toPos);
		position += toPos*0.05f;
		D3DXVECTOR3 Pos = targetpos - position;
		float len = D3DXVec3Length(&toPos);
		if (targetpos == position || len < 0.3f)
		{
			Btime = 0;
		}*/

	D3DXVECTOR3 toPos =m_targetPos- m_position;
	float len = D3DXVec3Length(&toPos);
	D3DXVec3Normalize(&toPos, &toPos);
	
	//移動
	m_position += toPos*m_bulletSpeed;
	m_bulletTime--;

	//バレットの寿命
	if (m_bulletTime <= 0 || len<m_bulletDeathlenge)
	{
		m_bulletDeadflg = true;
		m_isActive = false;
	}
}

void Bullet::BulletHit()
{
	const float			BossRadius = 3.0f;//ボスの半径
	const float			PlayerRadius = 0.3f;//プレイヤーの半径
	std::list<trackingEnemy*> enestl = SceneManager::GetGame().GetEnemyManager().GetEnemy();
	//バレットの当たり判定
	switch (m_chara)
	{

	case CHARA::TANK:
		m_light.SetAmbientLight(D3DXVECTOR4(8.0f, 0.0f, 8.0f, 1.0f));
		m_skinModel.SetLight(&m_light);
		if (CubeCollision::GetInstance().Cube(m_position, SceneManager::GetGame().GetPlayer().GetMiddlepos(), m_bulletRadius, PlayerRadius))
		{
			SceneManager::GetGame().GetPlayer().SetDamage();
			m_bulletDeadflg = true;
		}
		break;
	case CHARA::ENEMY:
		m_light.SetAmbientLight(D3DXVECTOR4(7.8f, 0.8f, 0.8f, 1.0f));
		m_skinModel.SetLight(&m_light);
		if (CubeCollision::GetInstance().Cube(m_position, SceneManager::GetGame().GetPlayer().GetMiddlepos(), m_bulletRadius, PlayerRadius))
		{
			SceneManager::GetGame().GetPlayer().SetDamage();
			m_bulletDeadflg = true;
		}

		if (&SceneManager::GetGame().GetBoss() == NULL)
		{
			break;
		}
		if (CubeCollision::GetInstance().Cube(m_position, SceneManager::GetGame().GetBoss().Getpos(), m_bulletRadius, BossRadius))
		{
			SceneManager::GetGame().GetBoss().SetDamage();
			m_bulletDeadflg = true;
		}

		break;
	case CHARA::PLAYER:
		m_light.SetAmbientLight(D3DXVECTOR4(7.8f, 7.8f, 0.8f, 1.0f));
		m_skinModel.SetLight(&m_light);
		for (auto ene : enestl)
		{
			if (CubeCollision::GetInstance().Cube(m_position,ene->GetPos(), m_bulletRadius,0.5f))
			{
				ene->SetActive(false);
				m_bulletDeadflg = true;
				m_breakSound->Init("Assets/Sound/sceneswitch2.wav");
				m_breakSound->SetVolume(0.4f);
				m_breakSound->Play(false);
			}
		}
		if (&SceneManager::GetGame().GetBoss() == NULL)
		{
			break;
		}
		if (CubeCollision::GetInstance().Cube(m_position, SceneManager::GetGame().GetBoss().Getpos(), m_bulletRadius, BossRadius))
		{
			SceneManager::GetGame().GetBoss().SetDamage();
			m_bulletDeadflg = true;
		}
		break;
	default:
		break;
	}
}

void Bullet::Draw()
{
	if (m_bulletDeadflg) { return; };
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	m_skinModel.Draw(&Camera::GetInstance().GetViewMatrix(), &Camera::GetInstance().GetProjectionMatrix());
}
