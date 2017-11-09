#include "stdafx.h"
#include "Bullet.h"
#include "CubeCollision.h"

SkinModelData* Bullet::skinModelData = NULL;

Bullet::Bullet()
{

}

Bullet::~Bullet()
{
	delete skinModelData;
	skinModelData = NULL;

}

void Bullet::Start(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos,int cha)
{
	m_Chara = cha;
	TargetPos = targetPos;
	//Number = No;
	position = pos;
	//skinModelData.LoadModelData("Assets/modelData/Bullet.X", NULL);
	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f,0.0f,-0.707f,1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f,  0.707f, -0.707f,1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.8f, 0.8f, 0.8f, 1.0f));

	Playerpos = game->GetPlayer()->Getpos();

	if (skinModelData == NULL){
		//モデルをロード。
		
		skinModelData = new SkinModelData;
		skinModelData->LoadModelData("Assets/modelData/Bullet.X", NULL);
	}
	skinModel.Init(skinModelData);
	skinModel.SetLight(&light);
	
	//D3DXQuaternionRotationAxis(&rotation, rotation,-5.0f);
	direction = { 0.0f, 0.0f, 1.0f };

	//state = eState_Search;
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
		float len = D3DXVec3Length(&Pos);
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
	D3DXVECTOR3 Ppos = game->GetPlayer()->Getpos();
	//直進バレット
	position += TargetPos*0.04f;
	//position.z += Ppos.z*0.04f;
	Btime--;

	//バレットの当たり判定
	if (Cubemass.Cubemass(position, Ppos, 0.3f, 0.3f))
	{
		switch (m_Chara)
		{
		case Player:

			break;

		case Enemy:
			game->GetPlayer()->SetDamage();
			Bulletflg = false;
			break;
		}
	}

	//バレットの寿命
	if (Btime <= 0 /*|| len<0.5f*/)
	{
		//Bulletflg = false;
		Btime = 300;
	}
}

void Bullet::Draw()
{
	skinModel.UpdateWorldMatrix(position, rotation/*D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0)*/, scale);

	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
