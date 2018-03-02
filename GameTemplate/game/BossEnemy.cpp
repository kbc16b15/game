#include "stdafx.h"
#include "BossEnemy.h"
#include "game.h"
#include "SceneManager.h"
#include "Player.h"
#include "BossHp.h"
#include "BulletManager.h"
#include "gameCamera.h"
#include "GameObjectManager.h"


//BossEnemy *BossEnemy::m_bossEnemy = NULL;

BossEnemy::BossEnemy()
{
	m_rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = { 0.7f,0.7f,0.7f };
	m_direction = { 0.0f,0.0f,1.0f };
	m_moveSpeed = { 0.0f,0.0f,0.0f };

}


BossEnemy::~BossEnemy()
{
	Release();
	//m_skinModelData.Release();
	//delete m_particleEmitter;
	////m_characterController.RemoveRigidBoby();
	////�@���}�b�v�J��
	//if (m_normalMap != NULL)
	//{
	//	m_normalMap->Release();
	//}

	////�X�y�L�����}�b�v�J��
	//if (m_specularMap != NULL)
	//{
	//	m_specularMap->Release();
	//}
	////�T�E���h�̊J��
	//if (m_bgmSound != nullptr)
	//{
	//	m_bgmSound->Release();
	//	m_bgmSound = nullptr;
	//}
	//if (m_beamSound != nullptr)
	//{
	//	m_beamSound->Release();
	//	m_beamSound = nullptr;
	//}
	//if (m_groundSound != nullptr)
	//{
	//	m_groundSound->Release();
	//	m_groundSound = nullptr;
	//}
}

void BossEnemy::Release()
{
	m_skinModelData.Release();
	//m_characterController.RemoveRigidBoby();
	if (m_particleEmitter != nullptr)
	{
		delete m_particleEmitter;
		m_particleEmitter = nullptr;
	}
	//�@���}�b�v�J��
	if (m_normalMap != NULL)
	{
		m_normalMap->Release();
	}

	//�X�y�L�����}�b�v�J��
	if (m_specularMap != NULL)
	{
		m_specularMap->Release();
	}
	//�T�E���h�̊J��
	if (m_bgmSound != nullptr)
	{
		m_bgmSound->Release();
		m_bgmSound = nullptr;
	}
	if (m_beamSound != nullptr)
	{
		m_beamSound->Release();
		m_beamSound = nullptr;
	}
	if (m_groundSound != nullptr)
	{
		m_groundSound->Release();
		m_groundSound = nullptr;
	}
}

void BossEnemy::Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	
	const float			charaHeight = 2.4f;	//�L�����̍���
	const float			charaGravity = -2.0f;//�L�����̏d��
	const float			BgmVolume = 0.2f;
	m_groundSound = new Sound;
	m_beamSound = new Sound;
	m_breakSound = new Sound;

	m_position = pos;
	m_rotation = rot;
	m_skinModelData.LoadModelData("Assets/modelData/Tank.X", NULL);
	m_skinModel.Init(&m_skinModelData);

	//���C�g���������B
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

	//�L�����N�^�R���g���[�����������B
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

	//�X�y�L�����}�b�v
	D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/TankSpecularMap.png",
		&m_specularMap);
	if (m_specularMap != NULL)
	{
		m_skinModel.SetSpecularMap(m_specularMap);
	}

	//�p�[�e�B�N���̏�����
	SParticleEmitParameter param;
	param.texturePath = "Assets/Particle/FY.png";
	param.w = 2.0f;
	param.h = 2.0f;
	param.Multipos = 1.5f;
	param.Multispeed = {0.5f,0.5f,0.5f};
	param.intervalTime = 0.6f;
	param.lifeTime = 2.5f;
	param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.position = m_characterController.GetPosition();

	m_particleEmitter = new ParticleEmitter;
	m_particleEmitter->Init(param);

	SceneManager::GetInstance().GetGame().BgmStop();
	//Game::GetInstance().BgmStop();
	m_bgmSound = new Sound();
	m_bgmSound->Init("Assets/Sound/Edge of the galaxy.wav", false);
	m_bgmSound->SetVolume(BgmVolume);
	m_bgmSound->Play(true);
}

void BossEnemy::Update()
{
	//if (&BossEnemy::GetInstance() == NULL || &BossHp::GetInstance() == NULL) { return; };
	if (m_isDeath) { return; }
	if (m_bgmSound != nullptr) {
		if (m_bgmSound->IsPlaying())
			m_bgmSound->Update();
	}
	//�G�l�~�[�̈ړ�����
	m_moveSpeed = m_characterController.GetMoveSpeed();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	
	switch (m_bossState)
	{
	case BossEnemyState::START:
		StartState();
		Damege();
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
		break;
	default:
		break;
	}

	if (m_groundSound != nullptr) {
		if (m_groundSound->IsPlaying())
			m_groundSound->Update();
	}
	if (m_beamSound != nullptr) {
		if (m_beamSound->IsPlaying())
			m_beamSound->Update();
	}
	if (m_breakSound != nullptr) {
		if (m_breakSound->IsPlaying())
			m_breakSound->Update();
	}

	m_middlePosition = m_characterController.GetPosition();
	m_middlePosition.y += m_charaRadius;
	//�L�����N�^���������x��ݒ�B
	m_characterController.SetMoveSpeed(m_moveSpeed);

	//�L�����N�^�R���g���[���[�����s�B
	m_characterController.Execute();

	m_skinModel.UpdateWorldMatrix(m_characterController.GetPosition(), m_rotation, m_scale);


}

void BossEnemy::StartState()
{
	m_startTime--;
	//gameCamera::GetInstance().BossStartCamera();

	if (m_characterController.IsOnGround() && m_startTime<0) {

		//Sound*	GroundSound = new Sound();
		const float GroundVolume = 0.7f;
		m_groundSound->Init("Assets/Sound/sceneswitch2.wav");
		m_groundSound->SetVolume(GroundVolume);
		m_groundSound->Play(false);
		m_bossState = BossEnemyState::STAND;
		//gameCamera::GetInstance().BossCamera();
		m_characterController.SetGravity(0.0f);
		m_characterController.RemoveRigidBoby();
	}

}

void BossEnemy::Stand()
{
	const float			rotLen = 50.0f;
	D3DXVECTOR3 pos = SceneManager::GetGame().GetPlayer().Getpos();
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
	m_attackTime--;
	const float		bossRadius = 3.0f;	//�{�X�̔��a
	const float		playerRadius = 0.3f;//�v���C���[�̔��a
	const float		bossAddMove = 1.5f;	//�ڕW���W�������Ɖ��ɂ��炷
	const float		moveAdd = 1.2f;		//��Z���x
	D3DXVECTOR3 toPos = SceneManager::GetGame().GetPlayer().Getpos() - m_characterController.GetPosition();
	
	float len=D3DXVec3Length(&toPos);
	if (!m_isTarget) {
		m_targetPos = SceneManager::GetGame().GetPlayer().Getpos() - m_characterController.GetPosition();
		m_targetPos.y = 0.0f;
		m_targetPos.x *= bossAddMove;
		m_targetPos.z *= bossAddMove;
		m_isTarget = true;
	}

	m_moveSpeed.x = m_targetPos.x*moveAdd;//�v���C���[�̍��W�܂ňړ�
	m_moveSpeed.z = m_targetPos.z*moveAdd;

	if (CubeCollision::GetInstance().Cube(m_characterController.GetPosition(), SceneManager::GetGame().GetPlayer().Getpos(), bossRadius, playerRadius))
	{
		SceneManager::GetGame().GetPlayer().SetDamage();
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
	const float		bulletSpeed = 0.5f;		//��Z���x
	m_rotTime--;
	float angle = atan2f(m_direction.x, m_direction.z);
	D3DXVECTOR3 Def;
	D3DXVec3Subtract(&Def, &m_characterController.GetPosition(), &SceneManager::GetGame().GetPlayer().Getpos());

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
		//Bullet* bullet = SceneManager::GetGame().GetBulletManager.CreateBullet(bullet->TANK);
		Bullet* bullet = new Bullet;
		//bullet->Init(m_characterController.GetPosition(), bulletSpeed, bullet->TANK);
		SceneManager::GetGame().GetBulletManager().AddBullets(bullet);
		bullet->Start(SceneManager::GetGame().GetPlayer().GetMiddlepos(), m_characterController.GetPosition(), bulletSpeed, bullet->TANK);
		m_bulletTime = m_bulletMaxTime;
		const float beamSoundVolume = 0.3f;
		//Sound* beamSound = new Sound();
		m_beamSound->Init("Assets/Sound/beamgun.wav");
		m_beamSound->SetVolume(beamSoundVolume);
		m_beamSound->Play(false);
	}

	if (m_rotTime < 0)
	{
		m_bossState = BossEnemyState::ATTACK;//�U����ԂɈڍs
		m_rotTime = m_maxrotTime;
	}
}

void BossEnemy::Damege()
{

	//�_���[�W����
	if (m_isDamageflg&&m_damageTime<0)
	{
		if (m_bossState!=BossEnemyState::DEAD)
		{
			m_isDamageflg = false;
			SceneManager::GetGame().GetBossHp().BossDamage(1);
			m_damageTime = m_damageMaxTime;
		}
		m_isDamageflg = false;
	}
	m_damageTime--;
	//HP���Ȃ��Ȃ����玀�S
	if (SceneManager::GetGame().GetBossHp().GetBossHpNum() <= 0)
	{

		m_bossState = BossEnemyState::DEAD;
	}
	
	if (SceneManager::GetGame().GetPlayer().GetPlayerDeath())
	{
		m_isDeath = true;
	}



}

void BossEnemy::Draw()
{
	if (m_isDeath) { return; }
	//�V���h�E���Z�b�g
	//m_skinModel.SetCasterflg(true);
	//m_skinModel.SetReciveflg(true);
	if (m_damageTime > 0 && (m_damageTime % 2) == 0) { return; }
	m_skinModel.Draw(&Camera::GetInstance().GetViewMatrix(), &Camera::GetInstance().GetProjectionMatrix());

	//�Q�[�����I��������
	if (SceneManager::GetInstance().GetGame().GetGameEnd())
	{
		m_isDeath = true;
		Release();
		return;
	}
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
		//Sound*	BreakSound = new Sound();
		m_breakSound->Init("Assets/Sound/sceneswitch2.wav");
		m_breakSound->SetVolume(m_soundBreakVolume);
		m_breakSound->Play(false);
		m_soundBreakTime = m_soundBreakMaxTime;
	}
	//gameCamera::GetInstance().BossEndCamera();
	if (m_deadTime < 0) 
	{ 
		SceneManager::GetInstance().GetGame().StageClear(true);
		GameObjectManager::GetGameObjectManager().DeleteGameObject(m_particleEmitter);

		m_isActive = false;
		m_isDeath = true;
	}
}
