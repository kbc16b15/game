#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine\HID\Pad.h"
//#include "IGameObject.h"

class Player/*:public IGameObject*/
{
public:
	Player();
	~Player();
	void Start();
	void Update();
	void Draw();
	void AnimationSet();
	void move();
	void Key();
	void BulletHit();

	D3DXVECTOR3 Getpos()
	{
		return characterController.GetPosition();
	}

	/*void setpos(D3DXVECTOR3 pos)
	{
		characterController.SetPosition(pos);
	}*/

	void SetJumpflg(bool Jump)
	{
		Jumpflg = Jump;
	}
	void AddSpeed(D3DXVECTOR3 addpos)
	{
		characterController.SetMoveSpeed(addpos);
		characterController.Execute();
	}

	D3DXVECTOR3 GetSpeed()
	{
		return characterController.GetMoveSpeed();
	}

	void SetDamage()
	{
		Damageflg = true;

	}
private:
	enum PlayerState
	{Stand, Move, Dash, Jump,Damage,Dead};
	bool				IsDead = false;
	bool				Isrun=false;
	bool				Ismove=false;
	bool				Isjump=false;
	bool				Jumpflg = false;
	bool				IsDamage = false;
	bool				IsStand = false;
	//bool				IsAnimend = true;
	bool				Damageflg = false;
	int					DamageTime = 200;
	SkinModel			skinModel;
	SkinModelData		skinModelData;
	Light				light;
	Animation			animation;
	CharacterController	characterController;
	D3DXVECTOR3			position = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3			scale = { 1.0f,1.0f,1.0f };
	D3DXQUATERNION		rotation = { 0.0f,0.0f,0.0f,1.0f };
	D3DXVECTOR3			moveSpeed = { 0.0f,0.0f,0.0f };
	Pad*				pad;

};

