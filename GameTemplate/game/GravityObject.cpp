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
	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
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
	position =/* locInfo.*/pos;
	rotation =/* locInfo.*/rot;

	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
	//ここから衝突判定絡みの初期化。
	//スキンモデルからメッシュコライダーを作成する。
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//続いて剛体を作成する。
	//まずは剛体を作成するための情報を設定。

	//rbInfo.collider = &meshCollider;//剛体のコリジョンを設定する。
	//rbInfo.mass = 0.0f;				//質量を0にすると動かない剛体になる。
	//rbInfo.pos = { 0.0f, 0.0f, 0.0f };
	//rbInfo.rot = { 0.0f, 0.0f, 0.0f, 1.0f };
	////剛体を作成。
	//rigidBody.Create(rbInfo);
	////作成した剛体を物理ワールドに追加。
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

	//0になったらフラグが入れかわるようにする？
	//関数呼んだだけでフラグが入れかわるようにする?
	position.z -= 0.02f;

	//btTransform& Ttra = rigidBody.GetBody()->getWorldTransform();//剛体の移動処理
	//Ttra.setOrigin({ position.x,position.y,position.z });
	//Ttra.setRotation({ rotation.x,rotation.y,rotation.z,rotation.w });
	//model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });

}

void GravityObject::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
