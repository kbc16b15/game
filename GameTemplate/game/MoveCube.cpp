#include "stdafx.h"
#include "MoveCube.h"


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

void MoveCube::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation)
{
	Spos = pos;
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.modelName*/modelName);
	//���f�������[�h�B
	modelData.LoadModelData(modelPath, NULL);
	//���[�h�������f���f�[�^���g����SkinModel���������B
	model.Init(&modelData);

	//���C�g���������B
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
	Rotation = rotation;

	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
	//��������Փ˔��藍�݂̏������B
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//�����č��̂��쐬����B
	//�܂��͍��̂��쐬���邽�߂̏���ݒ�B

	rbInfo.collider = &meshCollider;//���̂̃R���W������ݒ肷��B
	rbInfo.mass = 0.0f;				//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
	rbInfo.pos = position;
	rbInfo.rot = Rotation;
	//���̂��쐬�B
	rigidBody.Create(rbInfo);
	rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	rigidBody.GetBody()->setGravity({ 0.0f,0.0f,0.0f });

	//�쐬�������̂𕨗����[���h�ɒǉ��B
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
		if (len < 3.0f&&position.x>Limitpos.x)
		{
			//position.x -= 0.3f;
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
		if (len < 3.0f&&position.z>Limitpos.z)
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
		if (len < 3.0f&&position.z<Limitpos.z)
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
		if (len < 3.0f&&position.x<Limitpos.x)
		{
			position.x += 0.04f;
			D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
			speed.x += 0.8f;
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
		if (len < 2.5f&&position.y<Limitpos.y)
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
		
		if (len < 2.5f&&position.y>Limitpos.y)
		{
			Downflg = true;
			
		}
		if (Downflg)
		{
			position.y -= 0.04f;

		}
		break;
	default:
		break;
	}
	btTransform& Ttra = rigidBody.GetBody()->getWorldTransform();//���̂̈ړ�����
	Ttra.setOrigin({ position.x,position.y,position.z });
	Ttra.setRotation({ Rotation.x,Rotation.y,Rotation.z,Rotation.w });

	model.UpdateWorldMatrix(position, Rotation, { 1.0f,1.0f,1.0f });
}

void MoveCube::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}