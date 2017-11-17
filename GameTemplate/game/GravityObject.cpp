#include "stdafx.h"
#include "GravityObject.h"
//#include "myEngine/Physics/CollisionAttr.h"

GravityObject::GravityObject()
{
}


GravityObject::~GravityObject()
{
	/*g_physicsWorld->RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	modelData.Release();*/
}

void GravityObject::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	//mapObject->Init(modelName, pos, rot);
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
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
	position =/* locInfo.*/pos;
	rotation =/* locInfo.*/rot;

	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
	//��������Փ˔��藍�݂̏������B
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//�����č��̂��쐬����B
	//�܂��͍��̂��쐬���邽�߂̏���ݒ�B

	//rbInfo.collider = &meshCollider;//���̂̃R���W������ݒ肷��B
	//rbInfo.mass = 0.0f;				//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
	//rbInfo.pos = { 0.0f, 0.0f, 0.0f };
	//rbInfo.rot = { 0.0f, 0.0f, 0.0f, 1.0f };
	////���̂��쐬�B
	//rigidBody.Create(rbInfo);
	////�쐬�������̂𕨗����[���h�ɒǉ��B
	//g_physicsWorld->AddRigidBody(&rigidBody);
	//rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	//rigidBody.GetBody()->setUserIndex(enCollisionAttr_HitActive);
	//rigidBody.GetBody()->setUserIndex
}

void GravityObject::Update()
{
	/*GravityTime--;
	if (GravityTime > 0) { return; }
	D3DXVECTOR3 toPos;
	D3DXVec3Subtract(&toPos, &position, &game->GetPlayer()->Getpos());
	float len = D3DXVec3Length(&toPos);*/

	//if (len < length/*characterController.GetHit()*/)
	//{
	//	game->GetPlayer()->SetGravity();
	//	GravityTime = 200;
	//}

	//0�ɂȂ�����t���O�����ꂩ���悤�ɂ���H
	//�֐��Ă񂾂����Ńt���O�����ꂩ���悤�ɂ���?
	position.z -= 0.02f;

	//btTransform& Ttra = rigidBody.GetBody()->getWorldTransform();//���̂̈ړ�����
	//Ttra.setOrigin({ position.x,position.y,position.z });
	//Ttra.setRotation({ rotation.x,rotation.y,rotation.z,rotation.w });
	//model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });

}

void GravityObject::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
