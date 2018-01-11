#include "stdafx.h"
#include "Bullet.h"

SkinModelData* Bullet::m_skinModelData = NULL;

Bullet::Bullet()
{

}

Bullet::~Bullet()
{
	delete m_skinModelData;
	m_skinModelData = NULL;

}

void Bullet::Start(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos,int cha)
{
	//Number = No;
	//skinModelData.LoadModelData("Assets/modelData/Bullet.X", NULL);
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

	m_playerpos = g_game->GetPlayer()->Getpos();

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
	m_targetPos = targetPos;
	m_position = pos;
}


void Bullet::Update()
{
	//if (state == eState_Search)
	//{
	//	float angle = 0.0f;
	//	D3DXMATRIX matrix;
	//	D3DXMatrixRotationY(&matrix, angle);
	//	direction.x = matrix.m[2][0];
	//	direction.y = matrix.m[2][1];
	//	direction.z = matrix.m[2][2];


	//	//position += direction;
	//	D3DXVECTOR3 toPlayer = position- game->GetPlayer()->Getpos() ;
	//	D3DXVec3Normalize(&toPlayer, &toPlayer);
	//	angle = D3DXVec3Dot(&toPlayer, &direction);
	//	angle = acos(angle);

	//	D3DXVECTOR3 toPosition = position - game->GetPlayer()->Getpos();
	//	float tolen = D3DXVec3Length(&toPosition);

	//	if (fabsf(angle) < D3DXToRadian(125.0f)&& fabsf(angle) > D3DXToRadian(85.0f) &&tolen<3.0f)
	//	{
	//		state = eState_Find;
	//		//Hitflg = true;
	//	}

	//	
	//}
	//else if(state==eState_Find)
	//{
	//	D3DXVECTOR3 Up = { 0.0f,1.0f,0.0f };
	//	D3DXVECTOR3 AxisX = { 1.0f,0.0f,0.0f };
	//	D3DXVECTOR3 pPlayer = game->GetPlayer()->Getpos() - position;
	//	//Find = true;
	//	float angle=D3DXVec3Dot(&pPlayer,&AxisX);
	//	D3DXVec3Normalize(&pPlayer, &pPlayer);
	//	
	//	position += pPlayer*0.02f;
	//	D3DXQuaternionRotationAxis(&rotation, &Up, angle);
	//	//game->GetPlayer()->SetDamage();
	//	//Bulletflg = false;
	//}
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
		
		D3DXVECTOR3 Def;
		D3DXVec3Subtract(&Def, &position, &game->GetPlayer()->Getpos());

		float s;
		float halfAngle = atan2f(-Def.x, -Def.z) * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.x = 0.0f * s;
		rotation.y = 1.0f * s;
		rotation.z = 0.0f * s;
			*/

	CubeCollision Cubemass;
	D3DXVECTOR3 Ppos = g_game->GetPlayer()->Getpos();
	D3DXVECTOR3 toPos =m_targetPos- m_position;
	float len = D3DXVec3Length(&toPos);
	D3DXVec3Normalize(&toPos, &toPos);
	
	//直進バレット
	m_position += toPos*0.2f;
	m_btime--;

	//バレットの当たり判定
	if (Cubemass.Cubemass(m_position, Ppos, 0.3f, 0.3f))
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
	if (m_btime <= 0 || len<0.4f)
	{
		m_bulletflg = false;
		m_btime = 300;
	}
}

void Bullet::Draw()
{
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation/*D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0)*/, m_scale);

	m_skinModel.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());
}
