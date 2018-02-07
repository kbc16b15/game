#include "stdafx.h"
#include "MapChip.h"

//MapChip::MapChip()
//{
//	m_scale = { 1.0f,1.0f,1.0f, };
//}
//
//
//MapChip::~MapChip()
//{
//	PhysicsWorld::GetInstance().RemoveRigidBody(&m_rigidBody);
//	m_rigidBody.Release();
//	m_modelData.Release();
//}
//
//void MapChip::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
//{
//	//読み込むモデルのファイルパスを作成。
//	char modelPath[256];
//	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
//	//モデルをロード。
//	m_modelData.LoadModelData(modelPath, NULL);
//	//ロードしたモデルデータを使ってSkinModelを初期化。
//	m_model.Init(&m_modelData);
//
//	//ライトのセット
//	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
//	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
//	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
//	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));
//	//ライトカラーのセット
//	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
//	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
//	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
//	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
//	m_light.SetAmbientLight(D3DXVECTOR4(0.7f, 0.7f, 0.7f, 1.0f));
//
//	m_model.SetLight(&m_light);
//	m_position = pos;
//	m_rotation = rot;
//
//	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
//	//ここから衝突判定絡みの初期化。
//	//スキンモデルからメッシュコライダーを作成する。
//	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
//	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);
//	//続いて剛体を作成する。
//	//まずは剛体を作成するための情報を設定。
//
//	m_rbInfo.collider = &m_meshCollider;//剛体のコリジョンを設定する。
//	m_rbInfo.mass = 0.0f;				//質量を0にすると動かない剛体になる。
//	m_rbInfo.pos = m_position;
//	m_rbInfo.rot = m_rotation;
//	//剛体を作成。
//	m_rigidBody.Create(m_rbInfo);
//	//作成した剛体を物理ワールドに追加。
//	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);
//
//}
//
//void MapChip::Update()
//{
//	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
//}
//
//void MapChip::Draw()
//{
//	m_model.SetReciveflg(true);
//
//	m_model.Draw(&SpringCamera::GetInstance().GetViewMatrix(), &SpringCamera::GetInstance().GetProjectionMatrix());
//
//}