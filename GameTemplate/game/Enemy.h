#pragma once

#include "myEngine/Physics/CharacterController.h"
//#include "IGameObject.h"

class Enemy/*:public IGameObject*/
{
public:
	Enemy();
	~Enemy();
	void Start(D3DXVECTOR3 pos,int No);
	void Update();
	void Move();
	void Draw();
	void EnemyBullet();
	void Dead();

	D3DXVECTOR3 Getpos()
	{
		return position;
	}


	bool GetDeathflg()
	{
		return IsDeath;
	}

	bool GetDeadflg()
	{
		return IsDead;
	}

	int GetNo()
	{
		return Enemynum;
	}
private:

	void Setpos(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	enum EnemyMove
	{
		UP,
		DOWN,
	};
	EnemyMove			move = UP;
	SkinModel			skinModel;
	SkinModelData		skinModelData;

	D3DXVECTOR3			position = { -20.0f,0.0f,0.0f };
	D3DXVECTOR3			scale = { 0.5f,0.5f,0.5f };
	D3DXQUATERNION		rotation= D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	CharacterController	characterController;
	Light				light;

	int					BulletTime = 80;
	int					Enemynum = 0;
	int					bulletnum = 3;

	bool				IsDead = false;
	bool				IsDeath = false;

};

