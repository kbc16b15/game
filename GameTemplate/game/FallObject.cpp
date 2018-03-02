#include "stdafx.h"
#include "FallObject.h"
#include "Player.h"
#include "myEngine\Physics\Physics.h"

FallObject::FallObject(int sType)
{
	RotDir = { 0.0f, 0.0f, 1.0f };
	m_speed = sType;
}

void FallObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//firstpos = pos;
	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.modelName*/modelName);
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
	m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
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
	//rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	//m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeed);
	switch (m_speed)
	{
	case F:
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedF);
		break;
	case B:
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedB);
		//m_model.SetTextureMove(1);
		break;
	case R:
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedR);
		//m_model.SetTextureMove(1);
		break;
	case L:
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedL);
		//m_model.SetTextureMove(1);
		break;
	default:
		break;
	}
	m_model.SetTextureMove(true);
	//作成した剛体を物理ワールドに追加。
	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);
}

void FallObject::Update()
{
	D3DXVECTOR3 Pspeed = SceneManager::GetGame().GetPlayer().GetSpeed();
	D3DXVECTOR3 Ppos = SceneManager::GetGame().GetPlayer().Getpos();
	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = SceneManager::GetGame().GetPlayer().GetDir();
	if (!SceneManager::GetGame().GetPlayer().GetGround())
	{
		//m_isGround = true;
		m_speed = NONE;
	}

		switch (m_speed)
		{
		case F:
			speed.y = Pspeed.y;
			speed.z = m_addSpeed;
			SceneManager::GetGame().GetPlayer().AddSpeed(speed);
			break;
		case B:
			speed.y = Pspeed.y;
			speed.z = -m_addSpeed;
			SceneManager::GetGame().GetPlayer().AddSpeed(speed);
			break;
		case R:
			speed.y = Pspeed.y;
			speed.x = m_addSpeed;
			SceneManager::GetGame().GetPlayer().AddSpeed(speed);
			break;
		case L:
			speed.y = Pspeed.y;
			speed.x = -m_addSpeed;
			SceneManager::GetGame().GetPlayer().AddSpeed(speed);
			break;

		default:
			break;
		}

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f, });

}