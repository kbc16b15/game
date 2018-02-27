#include "stdafx.h"
#include "BossEnemy.h"
#include "game.h"
#include "Sound.h"
#include "Player.h"
#include "BossHp.h"
#include "BulletManager.h"
#include "gameCamera.h"
#include "GameObjectManager.h"


BossEnemy *BossEnemy::m_bossEnemy = NULL;

BossEnemy::BossEnemy()
{
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = { 0.7f,0.7f,0.7f };
	m_direction = { 0.0f,0.0f,1.0f };
	m_moveSpeed = { 0.0f,0.0f,0.0f };

}


BossEnemy::~BossEnemy()
{
	m_skinModelData.Release();
	delete m_particleEmitter;
	//m_characterController.RemoveRigidBoby();
	//法線マップ開放
	if (m_normalMap != NULL)
	{
		m_normalMap->Release();
	}

	//スペキュラマップ開放
	if (m_specularMap != NULL)
	{
		m_specularMap->Release();
	}
}

void BossEnemy::Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	
	const float			charaHeight = 2.4f;	//キャラの高さ
	const float			charaGravity = -2.0f;//キャラの重力

	Sound*	GroundSound = new Sound();
	GroundSound->Init("Assets/Sound/jump.wav");
	GroundSound->SetVolume(0.0f);
	GroundSound->Play(false);

	m_sPos = pos;
	m_position = pos;
	m_rotation = rot;
	m_skinModelData.LoadModelData("Assets/modelData/Tank.X", NULL);
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
	m_characterController.Init(m_charaRadius, charaHeight, m_position);
	m_characterController.SetGravity(charaGravity);

	m_skinModel.SetSpecularlight(true);

	D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/PA_ArchfireTankNorm.png",
		&m_normalMap);

	if (m_normalMap != NULL)
	{
		m_skinModel.SetnormalMap(m_normalMap);
	}

	//スペキュラマップ
	D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/TankSpecularMap.png",
		&m_specularMap);
	if (m_specularMap != NULL)
	{
		m_skinModel.SetSpecularMap(m_specularMap);
	}

	//パーティクルの初期化
	SParticleEmitParameter param;
	param.texturePath = "Assets/Particle/FY.png";
	param.w = 2.0f;
	param.h = 2.0f;
	param.Multipos = 1.5f;
	param.Multispeed = {0.5f,0.5f,0.5f};
	param.intervalTime = 0.6f;
	param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.position = m_characterController.GetPosition();

	m_particleEmitter = new ParticleEmitter;
	m_particleEmitter->Init(param);

}

void BossEnemy::Update()
{
	if (&BossEnemy::GetInstance() == NULL || &BossHp::GetInstance() == NULL) { return; };
	if (m_isDeath) { return; }
	//エネミーの移動処理
	m_moveSpeed = m_characterController.GetMoveSpeed();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	
	switch (m_bossState)
	{
	case BossEnemyState::START:
		StartState();
		break;
	case BossEnemyState::STAND:
		Stand();
		Damege();
		break;
	case BossEnemyState::ROT:
		rot();
		Damege();
		break;
	case BossEnemyState::ATTACK:
		Attack();
		Damege();
		break;
	case BossEnemyState::DEAD:
		Dead();
		if (m_isAddParticle) { break; }
		GameObjectManager::GetGameObjectManager().AddGameObject(m_particleEmitter);
		m_isAddParticle = true;
	default:
		break;
	}

	m_middlePosition = m_characterController.GetPosition();
	m_middlePosition.y += m_charaRadius;
	//キャラクタが動く速度を設定。
	m_characterController.SetMoveSpeed(m_moveSpeed);

	//キャラクタコントローラーを実行。
	m_characterController.Execute();

	m_skinModel.UpdateWorldMatrix(m_characterController.GetPosition(), m_rotation, m_scale);

}

void BossEnemy::StartState()
{
	m_startTime--;
	//gameCamera::GetInstance().BossStartCamera();

	if (m_characterController.IsOnGround() && m_startTime<0) {

		Sound*	GroundSound = new Sound();
		GroundSound->Init("Assets/Sound/jump.wav");
		GroundSound->SetVolume(0.4f);
		GroundSound->Play(false);
		m_bossState = BossEnemyState::STAND;
		//gameCamera::GetInstance().BossCamera();
		m_characterController.SetGravity(0.0f);
		m_characterController.RemoveRigidBoby();
	}

}

void BossEnemy::Stand()
{
	const float			rotLen = 50.0f;
	D3DXVECTOR3 pos = Player::GetInstance().Getpos();
	D3DXVECTOR3 toPos = pos - m_characterController.GetPosition();
	float len = D3DXVec3Length(&toPos);
	m_standTime--;
	if (m_standTime > 0)return;
	if (len < rotLen)
	{
		m_bossState = BossEnemyState::ROT;
	}
}

void BossEnemy::Attack()
{
	//if (m_isDead) { return; }
	m_attackTime--;
	const float		bossRadius = 3.0f;	//ボスの半径
	const float		playerRadius = 0.3f;//プレイヤーの半径
	const float		bossAddMove = 1.5f;	//目標座標をもっと奥にずらす
	const float		moveAdd = 1.2f;		//乗算速度
	D3DXVECTOR3 toPos = Player::GetInstance().Getpos() - m_characterController.GetPosition();
	
	float len=D3DXVec3Length(&toPos);
	if (!m_isTarget) {
		m_targetPos = Player::GetInstance().Getpos() - m_characterController.GetPosition();
		m_targetLen = D3DXVec3Length(&m_targetPos);
		m_targetPos.y = 0.0f;
		m_targetPos.x *= bossAddMove;
		m_targetPos.z *= bossAddMove;
		m_isTarget = true;
	}

	m_moveSpeed.x = m_targetPos.x*moveAdd;//プレイヤーの座標まで移動
	m_moveSpeed.z = m_targetPos.z*moveAdd;

	if (CubeCollision::GetInstance().Cube(m_characterController.GetPosition(), Player::GetInstance().Getpos(), bossRadius, playerRadius))
	{
		Player::GetInstance().SetDamage();
	}

	if (len > m_stopAttackLen||m_attackTime<0)
	{
		m_bossState = BossEnemyState::STAND;
		m_isTarget = false;
		m_standTime = m_maxStandTime;
		m_attackTime = m_maxAttackTime;
	}
}

void BossEnemy::rot()
{
	//if (m_isDead) { return; }
	const float		bulletSpeed = 0.5f;		//乗算速度
	m_rotTime--;
	float angle = atan2f(m_direction.x, m_direction.z);
	D3DXVECTOR3 Def;
	D3DXVec3Subtract(&Def, &m_characterController.GetPosition(), &Player::GetInstance().Getpos());

	float s;
	float halfAngle = atan2f(-Def.x, -Def.z) * 0.5f;
	s = sin(halfAngle);
	m_rotation.w = cos(halfAngle);
	m_rotation.x = 0.0f * s;
	m_rotation.y = 1.0f * s;
	m_rotation.z = 0.0f * s;

	m_bulletTime--;
	if (m_bulletTime < 0)
	{
		//Bullet* bullet = BulletManager::GetInstance().CreateBullet(bullet->TANK);
		Bullet* bullet = new Bullet;
		//bullet->Init(m_characterController.GetPosition(), bulletSpeed, bullet->TANK);
		BulletManager::GetInstance().AddBullets(bullet);
		bullet->Start(Player::GetInstance().GetMiddlepos(), m_characterController.GetPosition(), bulletSpeed, bullet->TANK);
		m_bulletTime = m_bulletMaxTime;
		const float beamSoundVolume = 0.3f;
		Sound* beamSound = new Sound();
		beamSound->Init("Assets/Sound/beamgun.wav");
		beamSound->SetVolume(beamSoundVolume);
		beamSound->Play(false);
	}

	if (m_rotTime < 0)
	{
		m_bossState = BossEnemyState::ATTACK;//攻撃状態に移行
		m_rotTime = m_maxrotTime;
	}
}

void BossEnemy::Damege()
{

	//ダメージ判定
	if (m_isDamageflg&&m_damageTime<0|| GetAsyncKeyState('G'))
	{
		if (m_bossState!=BossEnemyState::DEAD/*m_isDead == false*/)
		{
			m_isDamageflg = false;
			BossHp::GetInstance().BossDamage(1);
			m_damageTime = m_damageMaxTime;
		}
		m_isDamageflg = false;
	}
	m_damageTime--;

	//ゲームが終了したら
	if (Game::GetInstance().GetGameEnd())
	{
		m_isDeath = true;
	}
	//HPがなくなったら死亡
	if (BossHp::GetInstance().GetBossHp() <= 0)
	{
		m_bossState = BossEnemyState::DEAD;
	}


}

void BossEnemy::Draw()
{

	//シャドウをセット
	//m_skinModel.SetCasterflg(true);
	//m_skinModel.SetReciveflg(true);
	if (m_damageTime > 0 && (m_damageTime % 2) == 0) { return; }
	m_skinModel.Draw(&Camera::GetInstance().GetViewMatrix(), &Camera::GetInstance().GetProjectionMatrix());

	
}

void BossEnemy::HudDraw()
{
	//if (!m_isDead) {return;}
	//if (m_bossState != BossEnemyState::DEAD) { return; }
	//パーティクルの描画
	//m_particleEmitter->HudDraw(/*Camera::GetInstance().GetViewMatrix(), Camera::GetInstance().GetProjectionMatrix()*/);
}

void BossEnemy::Dead()
{
	//if (!m_isDead) { return; }
	m_deadTime--;
	m_soundBreakTime-= 1.0f / 60.0f;
	m_particleEmitter->SetPos(m_middlePosition);
	
	//m_particleEmitter.Update();
	if (m_soundBreakTime<0)
	{
		const float m_soundBreakVolume=0.4f;
		Sound*	BreakSound = new Sound();
		BreakSound->Init("Assets/Sound/sceneswitch2.wav");
		BreakSound->SetVolume(m_soundBreakVolume);
		BreakSound->Play(false);
		m_soundBreakTime = m_soundBreakMaxTime;
	}
	//gameCamera::GetInstance().BossEndCamera();
	if (m_deadTime < 0) 
	{ 
		Game::GetInstance().StageClear();
		GameObjectManager::GetGameObjectManager().DeleteGameObject(m_particleEmitter);
		
		m_isActive = false;
		//m_isDeath = true;
	}
}
