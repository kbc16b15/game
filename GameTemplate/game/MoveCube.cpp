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

	model.SetLight(&Game::GetInstance().GetLight());
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
	//rigidBody.GetBody()->setUserIndex(enCollisionAttr_ObjectHit);
	rigidBody.GetBody()->setGravity({ 0.0f,0.0f,0.0f });

	g_physicsWorld->AddRigidBody(&rigidBody);

}


void MoveCube::Update()
{
	/*D3DXVECTOR3 toPos;
	float len;*/
	
	//switch (MoveDir)
	//{
	//case FORWARD:
	//	D3DXVec3Subtract(&toPos, &position, &Player::GetInstance().Getpos());
	//	len = D3DXVec3Length(&toPos);
	//	if (len < 3.0f&&position.x>Limitpos.x&&Player::GetInstance().GetObjectHit())
	//	{

	//		position.x -= 0.04f;
	//		D3DXVECTOR3 speed = Player::GetInstance().GetSpeed();
	//		speed.x -=2.4f;
	//		Player::GetInstance().AddSpeed(speed);
	//	}
	//	else if (len > 3.0f&&position.x<Spos.x)
	//	{
	//		position.x += 0.04f;
	//	}
	//	break;
	//case LEFT:
	//	D3DXVec3Subtract(&toPos, &position, &Player::GetInstance().Getpos());
	//	len = D3DXVec3Length(&toPos);
	//	if (len < 3.0f&&position.z>Limitpos.z&&Player::GetInstance().GetObjectHit())
	//	{
	//		position.z -= 0.04f;
	//		D3DXVECTOR3 speed = Player::GetInstance().GetSpeed();
	//		speed.z -= 2.4f;
	//		Player::GetInstance().AddSpeed(speed);
	//	}
	//	else if (len > 3.0f&&position.z<Spos.z)
	//	{
	//		position.z += 0.04f;
	//	}
	//	break;
	//case RIGHT:
	//	D3DXVec3Subtract(&toPos, &position, &Game::GetInstance().GetPlayer()->Getpos());
	//	len = D3DXVec3Length(&toPos);
	//	if (len < 3.0f&&position.z<Limitpos.z&&Game::GetInstance().GetPlayer()->GetObjectHit())
	//	{
	//		position.z += 0.04f;
	//		D3DXVECTOR3 speed = Game::GetInstance().GetPlayer()->GetSpeed();
	//		speed.z += 2.4f;
	//		Game::GetInstance().GetPlayer()->AddSpeed(speed);
	//	}
	//	else if (len > 3.0f&&position.z>Spos.z)
	//	{
	//		position.z -= 0.04f;
	//	}
	//	break;
	//case BACK:
	//	D3DXVec3Subtract(&toPos, &position, &Game::GetInstance().GetPlayer()->Getpos());
	//	len = D3DXVec3Length(&toPos);
	//	if (len < 3.0f&&position.x<Limitpos.x&&Game::GetInstance().GetPlayer()->GetObjectHit())
	//	{
	//		position.x += 0.04f;
	//		D3DXVECTOR3 speed = Game::GetInstance().GetPlayer()->GetSpeed();
	//		speed.x += 1.f;
	//		Game::GetInstance().GetPlayer()->AddSpeed(speed);
	//	}
	//	else if (len > 3.0f&&position.x>Spos.x)
	//	{
	//		position.x -= 0.04f;
	//	}
	//	break;
	//case UP:
	//	D3DXVec3Subtract(&toPos, &position, &Game::GetInstance().GetPlayer()->Getpos());
	//	len = D3DXVec3Length(&toPos);
	//	if (len < 2.5f&&position.y<Limitpos.y&&Game::GetInstance().GetPlayer()->GetObjectHit())
	//	{
	//		position.y += 0.04f;
	//		D3DXVECTOR3 speed = Game::GetInstance().GetPlayer()->GetSpeed();
	//		speed.y += 2.4f;
	//		Game::GetInstance().GetPlayer()->AddSpeed(speed);
	//	}
	//	else if (len > 2.5f&&position.y>Spos.y)
	//	{
	//		position.y -= 0.04f;
	//	}
	//	break;
	//case DOWN:
	//	D3DXVec3Subtract(&toPos, &position, &Game::GetInstance().GetPlayer()->Getpos());
	//	len = D3DXVec3Length(&toPos);
	//	
	//	if (len < 3.0f&&position.y>Limitpos.y&&Game::GetInstance().GetPlayer()->GetObjectHit())
	//	{
	//		Downflg = true;
	//		//Game::GetInstance().GetPlayer()->SetObjectHit(false);
	//	}
	//	if (Downflg)
	//	{
	//		position.y -= 0.04f;

	//	}
	//	break;
	//default:
	//	break;
	//}
	//btTransform& Ttra = rigidBody.GetBody()->getWorldTransform();//„‘Ì‚ÌˆÚ“®ˆ—
	//Ttra.setOrigin({ position.x,position.y,position.z });
	//Ttra.setRotation({ rotation.x,rotation.y,rotation.z,rotation.w });

	//model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
}

void MoveCube::Draw()
{
	model.SetReciveflg(true);
	model.Draw(&Game::GetInstance().GetCamera()->GetViewMatrix(), &Game::GetInstance().GetCamera()->GetProjectionMatrix());
}