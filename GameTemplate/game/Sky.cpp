#include "stdafx.h"
#include "Sky.h"


Sky::Sky()
{
}


Sky::~Sky()
{
	//g_physicsWorld->RemoveRigidBody(&rigidBody);
	//rigidBody.Release();
	modelData.Release();
}

void Sky::Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{

	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
	//モデルをロード。
	modelData.LoadModelData(modelPath, NULL);
	//ロードしたモデルデータを使ってSkinModelを初期化。
	model.Init(&modelData);

	//ライトを初期化。
	light.SetAmbientLight(D3DXVECTOR4(0.8f, 0.8f, 0.8f, 1.0f));

	model.SetLight(&light);
	position =/* locInfo.*/pos;
	rotation =/* locInfo.*/rot;

	model.UpdateWorldMatrix(position, rotation, { 1.0f, 1.0f, 1.0f });
	//ここから衝突判定絡みの初期化。
	//スキンモデルからメッシュコライダーを作成する。
	//D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	//meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	////続いて剛体を作成する。
	////まずは剛体を作成するための情報を設定。

	//rbInfo.collider = &meshCollider;//剛体のコリジョンを設定する。
	//rbInfo.mass = 0.0f;				//質量を0にすると動かない剛体になる。
	//rbInfo.pos = { 0.0f, 0.0f, 0.0f };
	//rbInfo.rot = { 0.0f, 0.0f, 0.0f, 1.0f };
	////剛体を作成。
	//rigidBody.Create(rbInfo);
	////作成した剛体を物理ワールドに追加。
	//g_physicsWorld->AddRigidBody(&rigidBody);

	//rigidBody.GetBody()->setGravity({ 0.0f,0.0f,0.0f });
}

void Sky::Update()
{
	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f, });

}

void Sky::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}