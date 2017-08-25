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
	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.modelName*/modelName);
	//モデルをロード。
	modelData.LoadModelData(modelPath, NULL);
	//ロードしたモデルデータを使ってSkinModelを初期化。
	model.Init(&modelData);

	//ライトを初期化。
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
	//ここから衝突判定絡みの初期化。
	//スキンモデルからメッシュコライダーを作成する。
	/*D3DXMATRIX**/ rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//続いて剛体を作成する。
	//まずは剛体を作成するための情報を設定。

	rbInfo.collider = &meshCollider;//剛体のコリジョンを設定する。
	rbInfo.mass = 0.0f;				//質量を0にすると動かない剛体になる。
	rbInfo.pos = position;
	rbInfo.rot = Rotation;
	//剛体を作成。
	rigidBody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加。
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

	if (position != rbInfo.pos)//移動オブジェクトの重くなる原因
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