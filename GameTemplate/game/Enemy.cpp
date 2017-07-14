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

void Enemy::Start(D3DXVECTOR3 pos,int No)
{
	Enemynum = No;
	position = pos;
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
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

	//D3DXQUATERNION addRot;
	//D3DXQuaternionRotationAxis(&addRot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.1f);
	//rotation *= addRot;

	D3DXVECTOR3 toPos=position;
	toPos.y += 1.0f;
	D3DXVec3Subtract(&toPos, &toPos, &game->GetPlayer()->Getpos());
	float len = D3DXVec3Length(&toPos);
	if (len < 0.5f&&!IsDead)
	{
		game->GetPlayer()->SetJumpflg(true);
		IsDead = true;
	}

	skinModel.UpdateWorldMatrix(position, /*rotation*/D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0), scale);
	Dead();
}

void Enemy::Move()
{
	if (IsDead) { return; }
	switch (move)
	{
	case UP:
		position.y += 0.02f;
		break;
	case DOWN:
		position.y += -0.02f;
		break;
	}
	if (position.y <3.0f)
	{
		move =UP;
	}
	if (position.y>6.0f)
	{
		move = DOWN;
	}
}

void Enemy::EnemyBullet()
{
	D3DXVECTOR3 pos=game->GetPlayer()->Getpos();
	//D3DXVec3Subtract(&pos, &position, &game->GetPlayer()->Getpos());
	//float length = D3DXVec3Length(&pos);
	if (pos.x<=position.x) { return; }	//プレイヤーが左側にいる時だけ？
	if (IsDead) { return; }
	
	BulletTime--;
	if (BulletTime < 0/*&&bulletnum>-1*/)
	{
		Bullet* bullet = new Bullet();
		position.y += 0.5f;
		bullet->Start(position,Enemynum);
		position.y -= 0.5f;
		game->AddBullets(bullet);
		BulletTime = 80;
		bulletnum--;
	}
}

void Enemy::Dead()
{
	if (!IsDead){ return; }
	position.y -= 0.02f;
	if (position.y < -4.0f)
	{
		IsDeath = true;
	}

}

void Enemy::Draw()
{
	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}