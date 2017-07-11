#pragma once

#include "myEngine/Physics/CharacterController.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Start(D3DXVECTOR3 pos);
	void Update();
	void Move();
	void Render();
	void EnemyBullet();

	D3DXVECTOR3 Getpos()
	{
		return position;
	}

	void Setpos(D3DXVECTOR3 pos)
	{
		position = pos;
	}

private:
	enum EnemyMove
	{
		left,
		right,
	};
	EnemyMove			move = left;
	SkinModel			skinModel;
	SkinModelData		skinModelData;

	D3DXVECTOR3			position = { -20.0f,0.0f,0.0f };
	D3DXVECTOR3			scale = { 0.5f,0.5f,0.5f };
	D3DXQUATERNION		rotation= D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	CharacterController	characterController;
	Light				light;

	int					BulletTime = 60;

	bool				IsDead = false;


};

