#include "stdafx.h"
#include "MoveCube.h"
//#include "myEngine/Physics/CollisionAttr.h"

MoveCube::MoveCube(int Dir, D3DXVECTOR3 limitpos)
{
	MoveDir = Dir;
	Limitpos = limitpos;
}


MoveCube::~MoveCube()
{
	g_physicsWorld->RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	modelData.Release();
}

void MoveCube::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	Spos = pos;//‰ŠúÀ•W‚ÌŠi”[
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x",modelName);

	modelData.LoadModelData(modelPath, NULL);
	model.Init(&modelData);

	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	model.SetLight(&light);
	position = pos;
	rotation = rot;

	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();

	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);

	rbInfo.collider = &meshCollider;
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;

	rigidBody.Create(rbInfo);
	rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	rigidBody.GetBody()->setUserIndex(enCollisionAttr_ObjectHit);
	rigidBody.GetBody()->setGravity({ 0.0f,0.0f,0.0f });

	g_physicsWorld->AddRigidBody(&rigidBody);

}


void MoveCube::Update()
{
	D3DXVECTOR3 toPos;
	float len;
	
	switch (MoveDir)
	{
	case FORWARD:
		D3DXVec3Subtract(&toPos, &position, &game->GetPlayer()->Getpos());
		len = D3DXVec3Length(&toPos);
		if (len < 3.0f&&position.x>Limitpos.x&&game->GetPlayer()->GetObjectHit())
		{

			position.x -= 0.04f;
			D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
			speed.x -=2.4f;
			game->GetPlayer()->AddSpeed(speed);
		}
		else if (len > 3.0f&&position.x<Spos.x)
		{
			position.x += 0.04f;
		}
		break;
	case LEFT:
		D3DXVec3Subtract(&toPos, &position, &game->GetPlayer()->Getpos());
		len = D3DXVec3Length(&toPos);
		if (len < 3.0f&&position.z>Limitpos.z&&game->GetPlayer()->GetObjectHit())
		{
			position.z -= 0.04f;
			D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
			speed.z -= 2.4f;
			game->GetPlayer()->AddSpeed(speed);
		}
		else if (len > 3.0f&&position.z<Spos.z)
		{
			position.z += 0.04f;
		}
		break;
	case RIGHT:
		D3DXVec3Subtract(&toPos, &position, &game->GetPlayer()->Getpos());
		len = D3DXVec3Length(&toPos);
		if (len < 3.0f&&position.z<Limitpos.z&&game->GetPlayer()->GetObjectHit())
		{
			position.z += 0.04f;
			D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
			speed.z += 2.4f;
			game->GetPlayer()->AddSpeed(speed);
		}
		else if (len > 3.0f&&position.z>Spos.z)
		{
			position.z -= 0.04f;
		}
		break;
	case BACK:
		D3DXVec3Subtract(&toPos, &position, &game->GetPlayer()->Getpos());
		len = D3DXVec3Length(&toPos);
		if (len < 3.0f&&position.x<Limitpos.x&&game->GetPlayer()->GetObjectHit())
		{
			position.x += 0.04f;
			D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
			speed.x += 1.f;
			game->GetPlayer()->AddSpeed(speed);
		}
		else if (len > 3.0f&&position.x>Spos.x)
		{
			position.x -= 0.04f;
		}
		break;
	case UP:
		D3DXVec3Subtract(&toPos, &position, &game->GetPlayer()->Getpos());
		len = D3DXVec3Length(&toPos);
		if (len < 2.5f&&position.y<Limitpos.y&&game->GetPlayer()->GetObjectHit())
		{
			position.y += 0.04f;
			D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
			speed.y += 2.4f;
			game->GetPlayer()->AddSpeed(speed);
		}
		else if (len > 2.5f&&position.y>Spos.y)
		{
			position.y -= 0.04f;
		}
		break;
	case DOWN:
		D3DXVec3Subtract(&toPos, &position, &game->GetPlayer()->Getpos());
		len = D3DXVec3Length(&toPos);
		
		if (len < 2.7f&&position.y>Limitpos.y&&game->GetPlayer()->GetObjectHit())
		{
			Downflg = true;
			game->GetPlayer()->SetObjectHit(false);
		}
		if (Downflg)
		{
			position.y -= 0.04f;

		}
		break;
	default:
		break;
	}
	btTransform& Ttra = rigidBody.GetBody()->getWorldTransform();//„‘Ì‚ÌˆÚ“®ˆ—
	Ttra.setOrigin({ position.x,position.y,position.z });
	Ttra.setRotation({ rotation.x,rotation.y,rotation.z,rotation.w });

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
}

void MoveCube::Draw()
{
	model.SetReciveflg(true);
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}