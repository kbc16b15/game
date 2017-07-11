#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();
	void Start(D3DXVECTOR3 pos);
	void Update();
	void Render();
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
private:
	
	SkinModel			skinModel;
	SkinModelData		skinModelData;

	D3DXVECTOR3			position = { -50.0f,0.5f,0.0f };
	D3DXVECTOR3			scale = { 0.3f,0.3f,0.3f };
	D3DXQUATERNION		rotation;

	Light				light;

	int					Btime = 200;

	bool				Bulletflg = true;

	D3DXVECTOR3			targetpos;
};

