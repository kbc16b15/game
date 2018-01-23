#include "stdafx.h"
#include "Bullet.h"

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

void Bullet::Start(D3DXVECTOR3 pos,int cha)
{
	//ライトを初期化。
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f,0.0f,-0.707f,1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f,  0.707f, -0.707f,1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(7.8f, 0.8f, 0.8f, 1.0f));

	if (m_skinModelData == NULL){
		//モデルをロード。
		
		m_skinModelData = new SkinModelData;
		m_skinModelData->LoadModelData("Assets/modelData/Bullet.X", NULL);
	}
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetLight(&m_light);
	
	//D3DXQuaternionRotationAxis(&rotation, rotation,-5.0f);
	m_direction = { 0.0f, 0.0f, 1.0f };

	//state = eState_Search;
	m_Chara = cha;
	m_position = pos;
	m_targetPos=g_game->GetPlayer()->Getpos();

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
}


void Bullet::Update()
{
	
	TargetBullet();
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
		}
			*/

	CubeCollision Cubemath;
	D3DXVECTOR3 Ppos = g_game->GetPlayer()->Getpos();
	Ppos.y += m_playerUp;
	D3DXVECTOR3 toPos =m_targetPos- m_position;
	float len = D3DXVec3Length(&toPos);
	D3DXVec3Normalize(&toPos, &toPos);
	
	//直進バレット
	m_position += toPos*m_bulletSpeed;
	m_btime--;

	//バレットの当たり判定
	if (Cubemath.Cube(m_position, Ppos, m_bulletRadius, m_playerRadius))
	{
		switch (m_Chara)
		{
		case Player:

			break;

		case Enemy:
			g_game->GetPlayer()->SetDamage();
			m_bulletflg = false;
			break;
		}
	}

	//バレットの寿命
	if (m_btime <= 0 || len<m_bulletDeathlenge)
	{
		m_bulletflg = false;
		m_btime = 300;
	}
}

void Bullet::Draw()
{
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	m_skinModel.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());
}
