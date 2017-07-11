#include "stdafx.h"
#include "game.h"
#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Start(D3DXVECTOR3 pos)
{
	position = pos;
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	skinModelData.LoadModelData("Assets/modelData/Enemy.X", NULL);
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

void Enemy::Update()
{

	EnemyBullet();
	Move();
	D3DXQUATERNION addRot;

	D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.1f);
	rotation *= addRot;

	D3DXVECTOR3 toPos;
	position.y += 1.0f;
	D3DXVec3Subtract(&toPos, &position, &game->GetPlayer()->Getpos());
	float len = D3DXVec3Length(&toPos);

	if (len < 1.0f)
	{
		game->GetPlayer()->SetJumpflg(true);
		IsDead = true;
	}
	position.y -= 1.0f;

	if(IsDead)
	{
		position.y -= 0.02f;
	}
	skinModel.UpdateWorldMatrix(position, rotation/*D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0)*/, scale);
}

void Enemy::Move()
{
	switch (move)
	{
	case left:
		position.x += 0.05f;
		break;
	case right:
		position.x -= 0.05f;
		break;
	}
	if (position.x <-8.0f)
	{
		move = left;
	}
	else if (position.x>0.0)
	{
		move = right;
	}
}

void Enemy::EnemyBullet()
{
	if (IsDead) { return; }
	//std::list<Bullet*>& Blist = game->GetBullets();
	//for (auto bullet : Blist)
	//{

	//}

	BulletTime--;
	if (BulletTime < 0)
	{
		//std::vector<Bullet*> bulletstl = game->GetBullets();
		Bullet* bullet = new Bullet();
		position.y += 0.5f;
		bullet->Start(position);
		position.y -= 0.5f;
		game->AddBullets(bullet);
		BulletTime = 60;
	}
}

void Enemy::Render()
{
	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}