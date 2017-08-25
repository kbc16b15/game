#include "stdafx.h"
#include "game.h"
#include "MoveObject.h"

MoveObject::MoveObject()
{
}


MoveObject::~MoveObject()
{
}


void MoveObject::Init(const char* modelName,D3DXVECTOR3	pos,D3DXQUATERNION	rotation)
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
	position = /*locInfo.pos*/pos;
	Rotation = /*locInfo.rotation*/rotation;

	model.UpdateWorldMatrix(position, Rotation, { 1.0f, 1.0f, 1.0f });
	//��������Փ˔��藍�݂̏������B
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
	/*D3DXMATRIX**/ rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//�����č��̂��쐬����B
	//�܂��͍��̂��쐬���邽�߂̏���ݒ�B

	rbInfo.collider = &meshCollider;//���̂̃R���W������ݒ肷��B
	rbInfo.mass = 0.0f;				//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
	rbInfo.pos = position;
	rbInfo.rot = Rotation;
	//���̂��쐬�B
	rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	g_physicsWorld->AddRigidBody(&rigidBody);


	UMovelenge.x = position.x - 20.0f;
	RMovelenge.x = position.z + 2.0f;
	LMovelenge.x = position.z - 2.0f;
	DMovelenge.x = position.x;

}


void MoveObject::Update()
{

	D3DXVECTOR3 LPos = position;
	D3DXVECTOR3 RPos = position;
	D3DXVECTOR3 UPos = position;
	D3DXVECTOR3 DPos = position;
	D3DXVECTOR3 toPos;
	LPos.z += 2.4f;
	RPos.z -= 2.4f;
	UPos.x -= 2.8f;
	DPos.x += 2.4f;

	/*	D3DXVec3Subtract(&toPos, &LPos, &game->GetPlayer()->Getpos());
	float len= D3DXVec3Length(&toPos);
	if (len < 5.0f)
	{
	game->set(true);
	}
	*/
	D3DXVec3Subtract(&toPos, &LPos, &game->GetPlayer()->Getpos());
	float Llen = D3DXVec3Length(&toPos);

	if (Llen < 1.5f&&position.z<RMovelenge.x)
	{
		//moveSpeed.x = 4.0f;
		position.z += 0.1f;


	}

	D3DXVec3Subtract(&toPos, &RPos, &game->GetPlayer()->Getpos());
	float Rlen = D3DXVec3Length(&toPos);

	if (Rlen < 1.5f&&position.z>LMovelenge.x)
	{
		//moveSpeed.x = 4.0f;
		position.z -= 0.1f;

	}


	D3DXVec3Subtract(&toPos, &DPos, &game->GetPlayer()->Getpos());
	float Dlen = D3DXVec3Length(&toPos);

	if (Dlen < 1.0f&&position.x<DMovelenge.x)
	{
		//moveSpeed.x = 4.0f;
		position.x += 0.1f;


	}

	D3DXVec3Subtract(&toPos, &game->GetPlayer()->Getpos(), &UPos);
	float Ulen = D3DXVec3Length(&toPos);

	if (Ulen < 1.0f&&position.x >= UMovelenge.x)
	{
		//moveSpeed.x = 4.0f;
		position.x -= 0.1f;

	}

	if (position != rbInfo.pos)//�ړ��I�u�W�F�N�g�̏d���Ȃ錴��
	{
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);

		rbInfo.collider = &meshCollider;
		rbInfo.pos = position;
		rbInfo.rot = Rotation;
		rigidBody.Create(rbInfo);
		g_physicsWorld->AddRigidBody(&rigidBody);
	}

	model.UpdateWorldMatrix(position, Rotation, { 1.0f,1.0f,1.0f, });

	
}

void MoveObject::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}