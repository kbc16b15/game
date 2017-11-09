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
	characterController.RemoveRigidBoby();
}

void trackingEnemy::Start(D3DXVECTOR3 pos)
{
	//Spos = pos;
	position = pos;
	skinModelData.LoadModelData("Assets/modelData/ghost.X", NULL);
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

	//キャラクタコントローラを初期化。
	characterController.Init(0.8f, 1.0f, position);
	characterController.SetGravity(-10.0f);

}

void trackingEnemy::Update()
{
	Move();
	Dead();
	skinModel.UpdateWorldMatrix(characterController.GetPosition(), rotation, scale);

}

void trackingEnemy::Move()
{
	D3DXVECTOR3 Tpos = characterController.GetPosition();
	//エネミーの移動処理
	moveSpeed = characterController.GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	D3DXVECTOR3 pos = game->GetPlayer()->Getpos();
	D3DXVECTOR3 toPos = pos - characterController.GetPosition();
	float len = D3DXVec3Length(&toPos);
	D3DXVec3Normalize(&toPos, &toPos);
	switch (TState)
	{
	case SEACH:

		if (len < 5.0f)
		{
			TState = FOUND;
		}
		/*
		if (moveX)
		{
			moveSpeed.x = 3.0f;
		}
		else
		{
			moveSpeed.x = -3.0f;
		}
		*/
		if (Tpos.x<-18.0f)
		{
			moveX = true;
		}
		else if(Tpos.x>3.0f)
		{
			moveX = false;
		}
		break;
	case FOUND:
		if (len > 10.0f)
		{
			TState = SEACH;
		}
		//position += toPos*0.05f;
		moveSpeed += toPos*2.5f;

		float angle = atan2f(direction.x, direction.z);

		D3DXVECTOR3 Def;
		D3DXVec3Subtract(&Def, &characterController.GetPosition(), &pos);

		float s;
		float halfAngle = /*angle*/atan2f(-Def.x,-Def.z) * 0.5f;
		s = sin(halfAngle);
		rotation.w = cos(halfAngle);
		rotation.x = 0.0f * s;
		rotation.y = 1.0f * s;
		rotation.z = 0.0f * s;
		break;
	}

	//キャラクタが動く速度を設定。
	characterController.SetMoveSpeed(moveSpeed);

	//キャラクタコントローラーを実行。
	characterController.Execute();
}

void trackingEnemy::Draw()
{
	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}

void trackingEnemy::Dead()
{
	CubeCollision Cmass;
	if (Cmass.Cubemass(characterController.GetPosition(), game->GetPlayer()->Getpos(), 0.5f, 0.5f))
	{
		game->GetPlayer()->SetDamage();
		//IsDeath = true;
	}
}