#include "stdafx.h"
#include "MapChip.h"
#include "MoveObject.h"
#include "TrapObject.h"
#include "FallObject.h"
#include "GoalObject.h"
#include "HealItem.h"
#include "Spring.h"
#include "BoxChip.h"
#include "myEngine\Physics\Physics.h"

MapObject::MapObject()
{
	m_scale = { 1.0f,1.0f,1.0f, };
}


MapObject::~MapObject()
{
	PhysicsWorld::GetInstance().RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
	m_modelData.Release();
}

void MapObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
	//モデルをロード。
	m_modelData.LoadModelData(modelPath, NULL);
	//ロードしたモデルデータを使ってSkinModelを初期化。
	m_model.Init(&m_modelData);

	//ライトのセット
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));
	//ライトカラーのセット
	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(0.7f, 0.7f, 0.7f, 1.0f));

	m_model.SetLight(&m_light);
	m_position = pos;
	m_rotation = rot;

	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
	//ここから衝突判定絡みの初期化。
	//スキンモデルからメッシュコライダーを作成する。
	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);
	//続いて剛体を作成する。
	//まずは剛体を作成するための情報を設定。

	m_rbInfo.collider = &m_meshCollider;//剛体のコリジョンを設定する。
	m_rbInfo.mass = 0.0f;				//質量を0にすると動かない剛体になる。
	m_rbInfo.pos = m_position;
	m_rbInfo.rot = m_rotation;
	//剛体を作成。
	m_rigidBody.Create(m_rbInfo);
	//作成した剛体を物理ワールドに追加。
	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);

}

void MapObject::Update()
{
	m_model.UpdateWorldMatrix(m_position,m_rotation,m_scale);
}

void MapObject::Draw()
{
	m_model.SetReciveflg(true);

	m_model.Draw(&Camera::GetInstance().GetViewMatrix(), &Camera::GetInstance().GetProjectionMatrix());

}

MapObject* MapObject::MapReturn(const char* MapName)
{
	//ポリモーフィズムを使ったファクトリー
	//抽象クラスのインスタンスをポインタで作って、欲しいマップの型を返す
	MapObject* ob = nullptr;
	if (strcmp("MoveObject", MapName) == 0) {
		ob = new MoveObject();
	}
	else if (strcmp("BoxChip", MapName) == 0) {
		ob = new BoxChip();
	}
	else if (strcmp("TCircle", MapName) == 0) {
		ob = new TrapObject();
	}
	else if (strcmp("FCubeF", MapName) == 0) {
		ob = new FallObject(1);
	}
	else if (strcmp("FCubeB", MapName) == 0) {
		ob = new FallObject(2);
	}
	else if (strcmp("FCubeR", MapName) == 0) {
		ob = new FallObject(3);
	}
	else if (strcmp("FCubeL", MapName) == 0) {
		ob = new FallObject(4);
	}
	else if (strcmp("GoalObject", MapName) == 0) {
		ob = new GoalObject();
	}
	else if (strcmp("Boss", MapName) == 0) {
		//ob = new BoxChip();
	}
	else
	{
		ob = new MapChip();
	}
	return ob;
}