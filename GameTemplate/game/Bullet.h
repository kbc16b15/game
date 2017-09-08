#pragma once
//#include "IGameObject.h"
class Bullet/*:public IGameObject*/
{
public:
	Bullet();
	~Bullet();
	void Start(D3DXVECTOR3 pos);
	void Update();
	void Draw();
	void TargetBullet();

	bool GetBulletflg()
	{
		return Bulletflg;
	}

private:

	//enum EState {
	//	eState_Search,	//���G��ԁB
	//	eState_Find,	//������ԁB
	//};


	//EState state;		//�G�̏�ԁB

	SkinModel			skinModel;
	//SkinModelData		skinModelData;
	static SkinModelData* skinModelData;
	Light				light;
	D3DXVECTOR3			position = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3			scale = { 0.3f,0.3f,0.3f };
	D3DXQUATERNION		rotation=D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0);
	D3DXVECTOR3			targetpos;
	D3DXVECTOR3			direction;

	//bool				Find = false;
	int					Btime = 300;
	bool				Bulletflg = true;
};

