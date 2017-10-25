#include "stdafx.h"
#include "FallObject.h"
#include "myEngine/Physics/CollisionAttr.h"


FallObject::FallObject()
{
}


FallObject::~FallObject()
{
	g_physicsWorld->RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	modelData.Release();
}

void FallObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation)
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
	rigidBody.GetBody()->setUserIndex(enCollisionAttr_HitActive);
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	g_physicsWorld->AddRigidBody(&rigidBody);
	//angle = 85.0f;
}

void FallObject::Update()
{
	if (position.y < -1.0f)
	{
		position = firstpos;
	}
	angle += 0.05f;
	D3DXQUATERNION addRot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXQuaternionRotationAxis(&addRot, &RotDir, angle);
	Rotation = addRot;
	position.x -=FallSpeedx;
	position.y -=FallSpeedy;

	btTransform& Ttra = rigidBody.GetBody()->getWorldTransform();//���̂̈ړ�����
	Ttra.setOrigin({ position.x,position.y,position.z });
	Ttra.setRotation({ Rotation.x,Rotation.y,Rotation.z,Rotation.w });
	model.UpdateWorldMatrix(position, Rotation, { 1.0f,1.0f,1.0f, });

}

void FallObject::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix(), false, false);
}
