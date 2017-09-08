#include "stdafx.h"
#include "game.h"
#include "Enemy.h"
#include "Bullet.h"
#include "CubeCollision.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	
}

void Enemy::Start(D3DXVECTOR3 pos)
{
	position = pos;
	skinModelData.LoadModelData("Assets/modelData/Enemy.X", NULL);
	skinModel.Init(&skinModelData);

	//ライトを初期化。
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

void Enemy::Update()
{

	EnemyBullet();
	Move();

	CubeCollision Cmass;
	//position.y += 0.1f;
	if (Cmass.Cubemass(position, game->GetPlayer()->Getpos(),0.3f,0.3f))
	{
		game->GetPlayer()->SetJumpflg(true);
		IsDead = true;
	}
	//position.y -= 0.1f;
	skinModel.UpdateWorldMatrix(position,D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0), scale);
	Dead();
}

void Enemy::Move()
{
	
	//if (IsDead) { return; }

	//if (position.y<2.0f)
	//{
	//	move =UP;
	//}
	//if (position.y>6.0f)
	//{
	//	move = DOWN;
	//}
}

void Enemy::EnemyBullet()
{
	D3DXVECTOR3 pos=game->GetPlayer()->Getpos();
	if (pos.x<position.x){ return; }//プレイヤーが左側にいる時だけ？
	if (IsDead) { return; }
	
	BulletTime--;
	if (BulletTime < 0)
	{
		Bullet* bullet = new Bullet();
		bullet->Start(position);
		game->AddBullets(bullet);
		BulletTime = 150;
	}
}

void Enemy::Draw()
{
	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void Enemy::Dead()
{
	if (!IsDead) { return; }
	//position.y -= 0.02f;
	DeadTime--;
	//if (DeadTime<0)
	//{
		//characterController.RemoveRigidBoby();
		IsDeath = true;
	//}

	//IsDeath = true;

}