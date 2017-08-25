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
		return /*position*/characterController.GetPosition();
	}

	void SetJumpflg(bool Jump)
	{
		Jumpflg = Jump;
	}
private:
	enum PlayerState
	{Stand, Move, Dash, Jump,};
	bool				Isrun=false;
	bool				Ismove=false;
	bool				Isjump=false;

	//bool				IsStand = true;
	//bool				IsAnimend = true;

	bool				Testflg = false;
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

	bool				Jumpflg = false;
	int					JumpTime = 75;
	int					DamageTime = 0;
	
};

