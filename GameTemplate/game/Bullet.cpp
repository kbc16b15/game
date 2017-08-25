#include "stdafx.h"
#include "game.h"
#include "Bullet.h"

//SkinModelData* Bullet::ModelData = NULL;

Bullet::Bullet()
{
	
}

Bullet::~Bullet()
{
	//delete ModelData;
	//ModelData = NULL;
}

void Bullet::Start(D3DXVECTOR3 pos/*,int No*/)
{
	//Number = No;
	position = pos;
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	skinModelData.LoadModelData("Assets/modelData/Bullet.X", NULL);

	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f,0.0f,-0.707f,1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f,  0.707f, -0.707f,1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	targetpos = game->GetPlayer()->Getpos();

	//if (ModelData == NULL){
	//	//モデルをロード。
	//	ModelData = new SkinModelData;
	//	ModelData->LoadModelData("Assets/modelData/Bullet.X", NULL);
	//}
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	//direction = { 0.0f, 0.0f, 1.0f };

	//float PI = 3.14159265358979323846f;
	//float angle = ((rand() % 100) - 50) / 50.0f;
	//angle *= PI;

	//
	//D3DXMATRIX matrix;
	//D3DXMatrixRotationY(&matrix, angle);
	//direction.x = matrix.m[2][0];
	//direction.y = matrix.m[2][1];
	//direction.z = matrix.m[2][2];
	//D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);

}

void Bullet::Update()
{

	//std::vector<Enemy*>::iterator enemit;
	/*for (enemit= enemstl.begin();enemit!=enemstl.end();enemit++)
	{
		if ()
		{
			enemit
		}
	}*/

	//position += direction * 0.05f;
	//D3DXVECTOR3 toPlayer =  position- game->GetPlayer()->Getpos();
	//D3DXVec3Normalize(&toPlayer, &toPlayer);
	//float angle = D3DXVec3Dot(&toPlayer, &direction);
	//angle = acos(angle);

	//D3DXVECTOR3 toPosition =  position- game->GetPlayer()->Getpos();
	//float tolen=D3DXVec3Length(&toPosition);


	//if (fabsf(angle)<D3DXToRadian(45.0f)&&tolen<3.0f)
	//{
	//	Hitflg = true;
	//}
	TargetBullet();

	//position.x += 0.1f;
	skinModel.UpdateWorldMatrix(position,/* rotation*/D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0), scale);

}

void Bullet::TargetBullet()
{
	//追従バレット
	D3DXVECTOR3 toPos = targetpos - position;
	D3DXVec3Normalize(&toPos, &toPos);
	position += toPos*0.05f;
	D3DXVECTOR3 Pos = targetpos - position;
	float len = D3DXVec3Length(&Pos);
	/*if (targetpos == position||len<3.0f)
	{
		Btime = 0;
	}*/
	//直進バレット
	//position.x += 0.1;
	Btime--;
	
	if (Btime <= 0 || len<0.5f)
	{
		Bulletflg = false;
		/*std::vector<Enemy*> enemstl = game->Getenem();
		for (auto enemy : enemstl)
		{
			if (enemy->GetNo() == Number)
			{
				position = enemy->Getpos();

				if (enemy->GetDeadflg())
				{
					Bulletflg = false;
				}
			}
		}*/
		Btime = 300;
	}
}

void Bullet::Draw()
{
	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
