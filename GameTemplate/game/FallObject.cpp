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
	position = pos;
	rotation = rot;
	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
	//ここから衝突判定絡みの初期化。
	//スキンモデルからメッシュコライダーを作成する。
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//続いて剛体を作成する。
	//まずは剛体を作成するための情報を設定。

	rbInfo.collider = &meshCollider;//剛体のコリジョンを設定する。
	rbInfo.mass = 0.0f;				//質量を0にすると動かない剛体になる。
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成。
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
	//作成した剛体を物理ワールドに追加。
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
