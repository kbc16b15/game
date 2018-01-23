#include "stdafx.h"
#include "FallObject.h"
//#include "myEngine/Physics/CollisionAttr.h"


FallObject::FallObject(int sType)
{
	RotDir = { 0.0f, 0.0f, 1.0f };
	m_speed = sType;
}

FallObject::~FallObject()
{
	g_physicsWorld->RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	modelData.Release();
}

void FallObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	firstpos = pos;
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
	//rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	switch (m_speed)
	{
	case F:
		rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedF);
		break;
	case B:
		rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedB);
		break;
	case R:
		rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedR);
		break;
	case L:
		rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedL);
		break;
	default:
		break;
	}
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	g_physicsWorld->AddRigidBody(&rigidBody);
}

void FallObject::Update()
{
	D3DXVECTOR3 Pspeed = g_game->GetPlayer()->GetSpeed();
	D3DXVECTOR3 Ppos = g_game->GetPlayer()->Getpos();
	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = NONE;
	m_speed = g_game->GetPlayer()->GetDir();
	if (!g_game->GetPlayer()->GetGround())
	{
		m_speed = NONE;
	}


	switch (m_speed)
	{
	case F:
		//if (Ppos.x<position.x + 1.8f&&Ppos.x>position.x - 1.8f){
			speed.y = Pspeed.y;
			speed.z = m_addSpeed;
			g_game->GetPlayer()->AddSpeed(speed);
		//}
		break;
	case B:
		//if (Ppos.x<position.x + 1.8f&&Ppos.x>position.x - 1.8f){
			speed.y = Pspeed.y;
			speed.z = -m_addSpeed;
			g_game->GetPlayer()->AddSpeed(speed);
		//}
		break;
	case R:
		//if (Ppos.z<position.z + 1.8f&&Ppos.z>position.z - 1.8f){
			speed.y = Pspeed.y;
			speed.x = m_addSpeed;
			g_game->GetPlayer()->AddSpeed(speed);
		//}
		break;
	case L:
		//if (Ppos.z<position.z + 1.8f&&Ppos.z>position.z - 2.0f){
			speed.y = Pspeed.y;
			speed.x = -m_addSpeed;
			g_game->GetPlayer()->AddSpeed(speed);
		//}
		//else if(Ppos.z>position.z+5.0f)
		//{
		//	speed.y = Pspeed.y;
		//	speed.z = -0.3f/*m_addSpeed*/;
		//	g_game->GetPlayer()->AddSpeed(speed);
		//}
		//else if (Ppos.z<position.z-5.0f)
		//{
		//	speed.y = Pspeed.y;
		//	speed.z = -0.3f/*m_addSpeed*/;
		//	g_game->GetPlayer()->AddSpeed(speed);
		//}
		break;
	
	default:


		break;
	} 

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f, });

}

void FallObject::Draw()
{
	model.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());
}
