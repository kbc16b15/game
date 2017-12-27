#include "stdafx.h"
#include "TrapObject.h"
//#include "myEngine/Physics/CollisionAttr.h"

TrapObject::TrapObject(int Damagetype,D3DXVECTOR3 RDir)
{
	m_rotDir = RDir;
	m_damageType = Damagetype;
}


TrapObject::~TrapObject()
{
	g_physicsWorld->RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
	m_modelData.Release();
}

void TrapObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", modelName);
	//モデルをロード。
	m_modelData.LoadModelData(modelPath, NULL);
	//ロードしたモデルデータを使ってSkinModelを初期化。
	m_model.Init(&m_modelData);

	//ライトを初期化。
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

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
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Damage);
	//作成した剛体を物理ワールドに追加。
	g_physicsWorld->AddRigidBody(&m_rigidBody);
}


void TrapObject::Update()
{

	switch (m_damageType)
	{
	case STAND:
		break;
	case MOVE:
		break;
	case ROT:
		Rot();
		break;
	}

	/*std::list<Bullet*> bulletstl = g_game->GetBullet();
	for (auto bullet : bulletstl)
	{
		D3DXVECTOR3 Bulletpos=bullet->Getpos();
		D3DXVECTOR3 toPos = Bulletpos - g_game->GetPlayer()->Getpos();
		float len = D3DXVec3Length(&toPos);
		if (len < 0.8f)
		{
			rotflg = true;
		}

	}*/

	//D3DXVECTOR3 toPos = position - g_game->GetPlayer()->Getpos();
	//float len = D3DXVec3Length(&toPos);
	//if (len < 0.8f)
	//{
	//	rotflg = true;
	//}

	//剛体の移動処理	
	btTransform& Ttra = m_rigidBody.GetBody()->getWorldTransform();
	Ttra.setOrigin({ m_position.x,m_position.y,m_position.z });
	Ttra.setRotation({ m_rotation.x,m_rotation.y,m_rotation.z,m_rotation.w });
	
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f, });

}

void TrapObject::Rot()
{
		m_angle += 0.01f;
		D3DXQuaternionRotationAxis(&m_rotation, &m_rotDir, m_angle);
	
}

void TrapObject::Draw()
{
	m_model.SetReciveflg(true);
	m_model.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());
}
