#include "stdafx.h"
#include "MapObject.h"


MapObject::MapObject()
{
}


MapObject::~MapObject()
{
	//g_physicsWorld->RemoveRigidBody(&rigidBody);
	//rigidBody.Release();
	//modelData.Release();
}

//void MapObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
//{
//	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
//	char modelPath[256];
//	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
//	//���f�������[�h�B
//	modelData.LoadModelData(modelPath, NULL);
//	//���[�h�������f���f�[�^���g����SkinModel���������B
//	model.Init(&modelData);
//
//	//���C�g���������B
//	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
//	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
//	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
//	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));
//
//	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
//	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
//	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
//	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
//	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
//
//	model.SetLight(&light);
//	position =/* locInfo.*/pos;
//	rotation =/* locInfo.*/rot;
//
//	model.UpdateWorldMatrix(position, rotation, { 1.0f, 1.0f, 1.0f });
//	//��������Փ˔��藍�݂̏������B
//	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
//	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
//	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
//	//�����č��̂��쐬����B
//	//�܂��͍��̂��쐬���邽�߂̏���ݒ�B
//
//	rbInfo.collider = &meshCollider;//���̂̃R���W������ݒ肷��B
//	rbInfo.mass = 0.0f;				//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
//	rbInfo.pos = { 0.0f, 0.0f, 0.0f };
//	rbInfo.rot = { 0.0f, 0.0f, 0.0f, 1.0f };
//	//���̂��쐬�B
//	rigidBody.Create(rbInfo);
//	//�쐬�������̂𕨗����[���h�ɒǉ��B
//	g_physicsWorld->AddRigidBody(&rigidBody);
//}

//void MapObject::Update()
//{
//	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f, });
//}
//
//void MapObject::Draw()
//{
//	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix(),false,true);
//}
