#pragma once
//#include "IGameObject.h"
class Bullet/*:public IGameObject*/
{
public:
	Bullet();
	~Bullet();
	void Start(D3DXVECTOR3 pos,int No);
	void Update();
	void Draw();
	void TargetBullet();
	D3DXVECTOR3 Getpos()
	{
		return position;
	}

	void Setpos(D3DXVECTOR3 pos)
	{
		position = pos;
	}

	bool GetBulletflg()
	{
		return Bulletflg;
	}
	bool GetHitflg()
	{
		return Hitflg;
	}
	void SetHitflg(bool Hit)
	{
		Hitflg = Hit;
	}


private:
	

	SkinModel			skinModel;
	SkinModelData		skinModelData;
	D3DXVECTOR3			position = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3			scale = { 0.3f,0.3f,0.3f };
	D3DXQUATERNION		rotation=D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0);

	Light				light;

	int					Btime = 200;
	//int				bulletnumber = 0;
	bool				Bulletflg = true;
	bool				Hitflg = false;

	D3DXVECTOR3			targetpos;
	D3DXVECTOR3			direction;

	int					Number = 0;
};

