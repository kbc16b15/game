#include "stdafx.h"
#include "BulletWeapon.h"
#include "Player.h"
#include "Sound.h"
#include "BulletManager.h"
//#include "GameObjectManager.h"
#include "gameCamera.h"
#include "BulletHud.h"
#include "BossEnemy.h"

BulletWeapon::BulletWeapon()
{
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = { 0.7f,0.7f,0.7f };
	m_direction = { 0.0f,0.0f,1.0f };
	m_moveSpeed = { 0.0f,0.0f,0.0f };

}

BulletWeapon::~BulletWeapon()
{
	m_skinModelData.Release();
	//m_characterController.RemoveRigidBoby();
	if (m_normalMap != NULL)
	{
		m_normalMap->Release();
	}
}

void BulletWeapon::Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	m_position = pos;
	m_rotation = rot;
	//読み込むモデルのファイルパスを作成。
	m_skinModelData.LoadModelData("Assets/modelData/BulletWeapon.X", NULL);

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
	//m_characterController.Init(m_charaRadius, m_charaHeight, m_position);
	//m_characterController.SetGravity(0.0f);

	m_skinModel.SetSpecularlight(true);

	D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/weapon_Normal.png",
		&m_normalMap);

	if (m_normalMap != NULL)
	{
		m_skinModel.SetnormalMap(m_normalMap);
	}


}

void BulletWeapon::Update()
{
	if (m_isDead) { return; }
	//m_beamSound->Update();
	Move();
	Dead();

	if (m_moveSpeed.y > 0.0f)
	{
		m_moveSpeed.y = 0.0f;
	}
	//キャラクタが動く速度を設定。
	//m_characterController.SetMoveSpeed(m_moveSpeed);

	//キャラクタコントローラーを実行。

	//m_characterController.Execute();

	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void BulletWeapon::Move()
{
	if(&BossEnemy::GetInstance()==NULL)
	{
		return;
	}
	D3DXVECTOR3 pos = Player::GetInstance().Getpos();
	D3DXVECTOR3 toPos = pos - m_position;
	float len = D3DXVec3Length(&toPos);

	float angle = atan2f(m_direction.x, m_direction.z);
	D3DXVECTOR3 Def;
	D3DXVec3Subtract(&Def, &m_position, &BossEnemy::GetInstance().Getpos());

	float s;
	float halfAngle =atan2f(-Def.x, -Def.z) * 0.5f;
	const float bulletSpeed = 0.2f;
	switch (m_bulletWeaponState)
	{
	case STAND:

		if (len < m_playerBulletLenge)
		{
			m_bulletWeaponState = BULLET;
		}
		break;
	case BULLET:
		if (len > m_standLenge)
		{
			m_bulletWeaponState = STAND;
			m_isPlayerBulletCamera = false;
			gameCamera::GetInstance().SetRockCamera(false);
			Player::GetInstance().SetMove(false);
			BulletHud::GetInstance().SetBullet(false);
		}


		if (m_isPlayerBullet)
		{
			s = sin(halfAngle);
			m_rotation.w = cos(halfAngle);
			m_rotation.x = 0.0f * s;
			m_rotation.y = 1.0f * s;
			m_rotation.z = 0.0f * s;
		}

		m_bulletIntervalTime--;

		if (/*m_bulletIntervalTime < 0 && Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonB) ||*/m_bulletIntervalTime < 0 && GetAsyncKeyState('B') && m_isPlayerBulletCamera)
		{

			Bullet* bullet = BulletManager::GetInstance().CreateBullet(bullet->PLAYER);
			D3DXVECTOR3 BulletPos=m_position;
			BulletPos.y += 1.0f;
			bullet->Start(SpringCamera::GetInstance().GetTarTarget(), BulletPos, bulletSpeed, bullet->PLAYER);
			m_bulletIntervalTime = m_maxBulletTime;

			Sound* m_beamSound = new Sound();
			m_beamSound->Init("Assets/Sound/beamgun.wav");
			m_beamSound->SetVolume(m_beamVolume);
			m_beamSound->Play(false);
		}

		if (Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonA)||GetAsyncKeyState('Z'))//カメラ切り替え
		{
			if (!m_isPlayerBulletCamera)
			{
				m_isPlayerBulletCamera = true;
				m_isPlayerBullet = true;
				//ボスだけでなく2ステージめでも砲台をつかえるようにする？
				//砲台をボスの攻撃が当たらない場所に配置する
				//砲台をボスのバレットで破壊するようにする?
				gameCamera::GetInstance().SetRockCamera(true);
				Player::GetInstance().SetMove(true);
				BulletHud::GetInstance().SetBullet(true);
				
			}
			else{
				m_isPlayerBulletCamera = false;
				gameCamera::GetInstance().SetRockCamera(false);
				Player::GetInstance().SetMove(false);
				BulletHud::GetInstance().SetBullet(false);
			}
			
		}
		break;
	default:
		break;
	}
}

void BulletWeapon::Draw()
{
	m_skinModel.Draw(&SpringCamera::GetInstance().GetViewMatrix(), &SpringCamera::GetInstance().GetProjectionMatrix());
}

void BulletWeapon::Dead()
{
	if (Player::GetInstance().PlayerDeath())
	{
		m_isDeath = true;
	}
}