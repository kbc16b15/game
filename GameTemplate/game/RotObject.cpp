#include "stdafx.h"
#include "RotObject.h"

RotObject::RotObject(D3DXVECTOR3 RDir, D3DXVECTOR3 RSpeed,int Rottype)
{
	RotDir = RDir;
	RotSpeed = RSpeed;
	RotType = Rottype;
}
RotObject::RotObject(D3DXVECTOR3 RDir, D3DXVECTOR3 RSpeed)
{
	RotDir = RDir;
	RotSpeed = RSpeed;
}

RotObject::~RotObject()
{
	g_physicsWorld->RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	modelData.Release();
}


void RotObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
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
	rotation = rot;

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
	rbInfo.rot = rotation;
	//���̂��쐬�B
	rigidBody.Create(rbInfo);
	rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	g_physicsWorld->AddRigidBody(&rigidBody);

	//rigidBody.GetBody()->setUserIndex(enCollisionAttr_ObjectHit);

}

void RotObject::Update()
{
	D3DXVECTOR3 toPos;
	D3DXVec3Subtract(&toPos, &position, &g_game->GetPlayer()->Getpos());

	float len = D3DXVec3Length(&toPos);

	/*if (len <length&&g_game->GetPlayer()->GetObjectHit())
	{
		Tflg = true;
		g_game->GetPlayer()->SetObjectHit(false);
	}
	else
	{
		Tflg = false;
	}*/
	switch (RotType)
	{
		case ROT:
		if (Tflg)
		{
			D3DXVECTOR3 speed = g_game->GetPlayer()->GetSpeed();
			speed.x = RotSpeed.x/*-1.2f*/;
			speed.z = RotSpeed.z;
			g_game->GetPlayer()->AddSpeed(speed);
		}

		angle += 0.01f;
		break;
		//case CLOCK:
		//	if (Tflg)
		//	{
		//		D3DXVECTOR3 speed = g_game->GetPlayer()->GetSpeed();
		//		speed.x = RotSpeed.x/*-1.2f*/;
		//		speed.z = RotSpeed.z;
		//		g_game->GetPlayer()->AddSpeed(speed);
		//	}

		//	if (ClockRotTime < 0)
		//	{
		//		angle += 0.2f;
		//		ClockRotTime = 100;
		//	}
		//	else
		//	{
		//		ClockRotTime--;
		//	}
		//	break;
		case STAND:
			angle += rotSpeed;
			break;
		default:
			break;

	}
	//x += 0.01f;
	//z += 0.01f;
	//float s;
	//float halfAngle = atan2f(x,z) * 0.5f;
	//s = sin(halfAngle);
	//rotation.w = cos(halfAngle);
	//rotation.x = 0.0f * s;
	//rotation.y = 1.0f * s;
	//rotation.z = 0.0f * s;
	D3DXQuaternionRotationAxis(&rotation, &RotDir, angle);

	rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	btVector3 btPos;
	btPos.setX(position.x);
	btPos.setY(position.y);
	btPos.setZ(position.z);
	trans.setOrigin(btPos);
	btQuaternion btRot;
	btRot.setX(rotation.x);
	btRot.setY(rotation.y);
	btRot.setZ(rotation.z);
	btRot.setW(rotation.w);
	trans.setRotation(btRot);
	//btTransform& Ttra = rigidBody.GetBody()->getWorldTransform();//���̂̈ړ�����
	//Ttra.setOrigin({ position.x,position.y,position.z });
	//Ttra.setRotation({ rotation.x,rotation.y,rotation.z,rotation.w });

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f});

}

void RotObject::Draw()
{
	model.SetReciveflg(true);
	model.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());
}