#include "stdafx.h"
#include "trackingEnemy.h"
#include "Enemy.h"
#include "Bullet.h"
#include "CubeCollision.h"

trackingEnemy::trackingEnemy()
{
}

trackingEnemy::~trackingEnemy()
{
	skinModelData.Release();
}

void trackingEnemy::Start(D3DXVECTOR3 pos)
{
	//Spos = pos;
	position = pos;
	skinModelData.LoadModelData("Assets/modelData/Enemy2.X", NULL);
	skinModel.Init(&skinModelData);

	//ƒ‰ƒCƒg‚ð‰Šú‰»B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	skinModel.SetLight(&light);

}

void trackingEnemy::Update()
{
	EnemyBullet();
	CubeCollision Cmass;
	if (Cmass.Cubemass(position, game->GetPlayer()->Getpos(), 0.4f, 0.3f))
	{
		game->GetPlayer()->SetDamage();
		IsDeath = true;
	}
	skinModel.UpdateWorldMatrix(position, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0), scale);
	Dead();
}

void trackingEnemy::EnemyBullet()
{
	D3DXVECTOR3 pos = game->GetPlayer()->Getpos();

	D3DXVECTOR3 toPos = pos - position;
	float len = D3DXVec3Length(&toPos);


	D3DXVec3Normalize(&toPos, &toPos);
	
	if (len < 10.0f)
	{
		position += toPos*0.05f;
	}
}

void trackingEnemy::Draw()
{
	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix(), false, true);
}

void trackingEnemy::Dead()
{
}