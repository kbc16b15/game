#include "stdafx.h"
#include "GoalObject.h"
#include "Player.h"
#include "game.h"
#include "Map.h"
//GoalObject::GoalObject()
//{
//}

//void GoalObject::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
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
//	m_position =pos;
//	m_rotation =rot;
//
//	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
//	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
//
//	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);
//
//	m_rbInfo.collider = &m_meshCollider;
//	m_rbInfo.mass = 0.0f;
//	m_rbInfo.pos = m_position;
//	m_rbInfo.rot = m_rotation;
//
//	m_rigidBody.Create(m_rbInfo);
//	//rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
//	m_rigidBody.GetBody()->setGravity({ 0.0f,0.0f,0.0f });
//
//	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);
//
//	//パーティクルの初期化
//	//SParticleEmitParameter param;
//	//param.texturePath = "ray.png";
//	//param.w = 0.5f;
//	//param.h = 0.5f;
//	//param.intervalTime = 0.2f;
//	//param.initSpeed = D3DXVECTOR3(0.0f, 3.5f, 0.0f);
//	//D3DVECTOR pPos = m_position;
//	//pPos.y += 2.0f;
//	//param.position = Player::GetInstance().Getpos()/*pPos*/;
//	//m_particleEmitter.Init(param);
//}

void GoalObject::Update()
{
	//m_particleEmitter.Update();
	D3DXVECTOR3 toPos = m_position - Player::GetInstance().Getpos();
	float len = D3DXVec3Length(&toPos);
	if (len < 2.5f||GetAsyncKeyState('N'))
	{
		Game::GetInstance().NextStage();
		//Player::GetInstance().Setpos(Map::GetInstance().GetMapPlayerPos());
		
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f, });
}

//void GoalObject::Draw()
//{
//
//	m_model.Draw(&SpringCamera::GetInstance().GetViewMatrix(), &SpringCamera::GetInstance().GetProjectionMatrix());
//
//	D3DXVECTOR3 toPos = m_position - Player::GetInstance().Getpos();
//	float plen = D3DXVec3Length(&toPos);
//	//m_particleEmitter.Render(SpringCamera::GetInstance().GetViewMatrix(), SpringCamera::GetInstance().GetProjectionMatrix());
//
//	//if (plen < 50.0f)
//	//{
//	//	//パーティクルの描画
//	//	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
//	//	m_particleEmitter.Render(SpringCamera::GetInstance().GetViewMatrix(), SpringCamera::GetInstance().GetProjectionMatrix());
//	//	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
//	//}
//
//}
