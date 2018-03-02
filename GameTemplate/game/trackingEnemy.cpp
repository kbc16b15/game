#include "stdafx.h"
#include "trackingEnemy.h"
#include "Player.h"
#include "BulletManager.h"
#include "GameObjectManager.h"

trackingEnemy::trackingEnemy()
{
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = { 0.7f,0.7f,0.7f };
	m_direction = { 0.0f,0.0f,1.0f };
	m_moveSpeed = { 0.0f,0.0f,0.0f };
	
}

trackingEnemy::~trackingEnemy()
{
	m_skinModelData.Release();
	//m_characterController.RemoveRigidBoby();
	if (m_particleEmitter != nullptr)
	{
		delete m_particleEmitter;
		m_particleEmitter = nullptr;
	}
	
	if (m_normalMap != NULL)
	{
		m_normalMap->Release();
	}
}

void trackingEnemy::Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	//m_sPos = pos;
	m_position = pos;
	m_rotation = rot;
	//読み込むモデルのファイルパスを作成。
	//char modelPath[256];
	//sprintf(modelPath, "Assets/modelData/%s.x",modelName);

	////モデルをロード。
	//m_skinModelData.LoadModelData(modelPath, NULL);
	////ロードしたモデルデータを使ってSkinModelを初期化。
	//m_skinModel.Init(&m_skinModelData);

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
	/*m_characterController.Init(m_charaRadius, m_charaHeight, m_position);
	m_characterController.SetGravity(0.0f);*/
	
	m_skinModel.SetSpecularlight(true);

	D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/PA_DroneNorm.png",
		&m_normalMap);

	if (m_normalMap != NULL)
	{
		m_skinModel.SetnormalMap(m_normalMap);
	}
	m_beamSound = new Sound;
	//パーティクルの初期化
	SParticleEmitParameter param;
	param.texturePath = "Assets/Particle/FY.png";
	param.w = 1.5f;
	param.h = 1.5f;
	param.Multipos = 0.5f;
	param.Multispeed = { 0.5f,0.5f,0.5f };
	param.intervalTime = 0.3f;
	param.lifeTime = 0.6f;
	param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.position =m_position;

	m_particleEmitter = new ParticleEmitter;
	m_particleEmitter->Init(param);
}

void trackingEnemy::Update()
{
	if (m_isDeath) { return; }
	if (!m_isDead) {
		Move();
	}
	Dead();
	if (m_beamSound != nullptr) {
		if (m_beamSound->IsPlaying())
			m_beamSound->Update();
	}
	if (m_moveSpeed.y > 0.0f)
	{
		m_moveSpeed.y = 0.0f;
	}
	//キャラクタが動く速度を設定。
	//m_characterController.SetMoveSpeed(m_moveSpeed);

	//キャラクタコントローラーを実行。

	//m_characterController.Execute();
	
	m_skinModel.UpdateWorldMatrix(m_position/*m_characterController.GetPosition()*/, m_rotation, m_scale);


}

void trackingEnemy::Move()
{
	//D3DXVECTOR3 Tpos = characterController.GetPosition();
	//エネミーの移動処理
	//m_moveSpeed = m_characterController.GetMoveSpeed();
	//m_moveSpeed.x = 0.0f;
	//m_moveSpeed.z = 0.0f;

	D3DXVECTOR3 toPos = SceneManager::GetGame().GetPlayer().Getpos() - m_position/*m_characterController.GetPosition()*/;
	float len = D3DXVec3Length(&toPos);

	float angle = atan2f(m_direction.x, m_direction.z);
	D3DXVECTOR3 Def;
	D3DXVec3Subtract(&Def, &m_position/*m_characterController.GetPosition()*/, &SceneManager::GetGame().GetPlayer().Getpos());

	float s;
	float halfAngle = /*angle*/atan2f(-Def.x, -Def.z) * 0.5f;
	const float bulletSpeed = 0.2f;
	switch (m_trackingState)
	{
	case SEACH:

		if (len < m_foundLenge)
		{
			m_trackingState = FOUND;
		}

		break;
	case FOUND:
		if (len > m_seachLenge)
		{
			m_trackingState = SEACH;
		}
		toPos.y = 0.0f;
		/*m_moveSpeed*///m_position += toPos*m_enemySpeed;

		s = sin(halfAngle);
		m_rotation.w = cos(halfAngle);
		m_rotation.x = 0.0f * s;
		m_rotation.y = 1.0f * s;
		m_rotation.z = 0.0f * s;

		m_bulletIntervalTime--;

		if (m_bulletIntervalTime < 0)
		{
			
			//PlayerPos.y += PlayerRadius;
			//Bullet* bullet=BulletManager::GetInstance().CreateBullet(bullet->ENEMY);
			Bullet* bullet = new Bullet;
			SceneManager::GetGame().GetBulletManager().AddBullets(bullet);
			bullet->Start(SceneManager::GetGame().GetPlayer().GetMiddlepos(),m_position, bulletSpeed, bullet->ENEMY);
			m_bulletIntervalTime = m_maxBulletTime;

			//Sound* m_beamSound = new Sound();
			m_beamSound->Init("Assets/Sound/beamgun.wav");
			m_beamSound->SetVolume(m_beamVolume);
			m_beamSound->Play(false);
		}
		break;
	default:
		break;
	}
}

void trackingEnemy::Draw()
{
	m_skinModel.Draw(&Camera::GetInstance().GetViewMatrix(), &Camera::GetInstance().GetProjectionMatrix());
}

void trackingEnemy::Dead()
{
	if (SceneManager::GetGame().GetPlayer().GetPlayerDeath())
	{
		m_isDeath = true;
	}
	if (m_isDead&&!m_isParticle)
	{
		GameObjectManager::GetGameObjectManager().AddGameObject(m_particleEmitter);
		m_isParticle = true;
	}
	if (m_isParticle) {
		m_deadTime--;
	}
	if (m_deadTime<0&&m_isParticle)
	{
		GameObjectManager::GetGameObjectManager().DeleteGameObject(m_particleEmitter);
		m_isDeath = true;
	}

}