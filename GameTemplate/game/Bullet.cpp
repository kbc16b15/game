#include "stdafx.h"
#include "game.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::Start(D3DXVECTOR3 pos)
{
	position = pos;
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	skinModelData.LoadModelData("Assets/modelData/Bullet.X", NULL);
	skinModel.Init(&skinModelData);

	//ƒ‰ƒCƒg‚ð‰Šú‰»B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f,0.0f,-0.707f,1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f,  0.707f, -0.707f,1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	skinModel.SetLight(&light);
	targetpos = game->GetPlayer()->Getpos();

	//float PI = 3.14159265358979323846f;
	//float angle = ((rand() % 100) - 50) / 50.0f;
	//angle *= PI;

	/*D3DXVECTOR3 direction;
	D3DXMATRIX matrix = skinModel.GetOrgMeshFirst;
	D3DXMatrixRotationY(&matrix, angle);
	direction.x = matrix.m[2][0];
	direction.y = matrix.m[2][1];
	direction.z = matrix.m[2][2];*/
}

void Bullet::Update()
{

	//D3DXVec3Normalize(&direction, &direction);
	//D3DXVECTOR3 Pos;
	//D3DXVec3Subtract(&Pos, &game->GetPlayer()->Getpos(), &position);
	//D3DXVec3Normalize(&Pos, &Pos);
	//float angles = 0.0f;
	//angles = D3DXVec3Dot(&direction,&direction);
	//angles = acos(angles);


	TargetBullet();
	//position.x += 0.1f;
	skinModel.UpdateWorldMatrix(position, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0), scale);
}

void Bullet::TargetBullet()
{

	D3DXVECTOR3 toPos = targetpos - position;
	D3DXVec3Normalize(&toPos, &toPos);
	position += toPos*0.05;
	D3DXVECTOR3 Pos = targetpos - position;
	float len = D3DXVec3Length(&Pos);

	Btime--;
	if (Btime < 0 || len<0.5f)
	{
		Bulletflg = false;
		Btime = 200;
	}
}

void Bullet::Render()
{
	skinModel.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
