#include "stdafx.h"
#include "trackingEnemy.h"
#include "Player.h"
#include "Sound.h"
#include "BulletManager.h"

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
	m_characterController.RemoveRigidBoby();
	if (m_normalMap != NULL)
	{
		m_normalMap->Release();
	}
}

void trackingEnemy::Init(D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	m_sPos = pos;
	m_position = pos;
	m_rotation = rot;
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	//char modelPath[256];
	//sprintf(modelPath, "Assets/modelData/%s.x",modelName);

	////���f�������[�h�B
	//m_skinModelData.LoadModelData(modelPath, NULL);
	////���[�h�������f���f�[�^���g����SkinModel���������B
	//m_skinModel.Init(&m_skinModelData);

	m_skinModelData.LoadModelData("Assets/modelData/Drone.X", NULL);

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
	m_characterController.Init(m_charaRadius, m_charaHeight, m_position);
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

void trackingEnemy::Update()
{
	if (m_isDead) { return; }
	//m_beamSound->Update();
	Move();
	Dead();

	if (m_moveSpeed.y > 0.0f)
	{
		m_moveSpeed.y = 0.0f;
	}
	//�L�����N�^���������x��ݒ�B
	m_characterController.SetMoveSpeed(m_moveSpeed);

	//�L�����N�^�R���g���[���[�����s�B

	//m_characterController.Execute();
	
	m_skinModel.UpdateWorldMatrix(m_characterController.GetPosition(), m_rotation, m_scale);

}

void trackingEnemy::Move()
{
	//D3DXVECTOR3 Tpos = characterController.GetPosition();
	//�G�l�~�[�̈ړ�����
	m_moveSpeed = m_characterController.GetMoveSpeed();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	D3DXVECTOR3 pos = Player::GetInstance().Getpos();
	D3DXVECTOR3 toPos = pos - m_characterController.GetPosition();
	float len = D3DXVec3Length(&toPos);

	float angle = atan2f(m_direction.x, m_direction.z);
	D3DXVECTOR3 Def;
	D3DXVec3Subtract(&Def, &m_characterController.GetPosition(), &pos);

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
		m_moveSpeed += toPos*m_enemySpeed;

		s = sin(halfAngle);
		m_rotation.w = cos(halfAngle);
		m_rotation.x = 0.0f * s;
		m_rotation.y = 1.0f * s;
		m_rotation.z = 0.0f * s;

		m_bulletIntervalTime--;

		if (m_bulletIntervalTime < 0)
		{

			Bullet* bullet=BulletManager::GetInstance().CreateBullet(bullet->ENEMY);
			bullet->Init(m_characterController.GetPosition(), bulletSpeed, bullet->ENEMY);
			m_bulletIntervalTime = m_maxBulletTime;

			Sound* m_beamSound = new Sound();
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
	m_skinModel.Draw(&SpringCamera::GetInstance().GetViewMatrix(), &SpringCamera::GetInstance().GetProjectionMatrix());
}

void trackingEnemy::Dead()
{
	if (Player::GetInstance().PlayerDeath())
	{
		m_isDeath = true;
	}
	/*CubeCollision Cubemath;
	if (Cmass.Cubemath(m_characterController.GetPosition(), Player::GetInstance().Getpos(), 0.5f, 0.5f))
	{
		Player::GetInstance().SetDamage();
		m_isDeath = true;
	}*/

}