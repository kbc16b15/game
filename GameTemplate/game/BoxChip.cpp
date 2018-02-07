#include "stdafx.h"
#include "BoxChip.h"

//BoxChip::BoxChip()
//{
//}

void BoxChip::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
	//モデルをロード。
	//m_modelData.CloneModelData(m_modelData, NULL);
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

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
	//衝突判定絡みの初期化。
	m_boxCollider.Create({ 2.1f, 1.0f,2.1f });

	//剛体を作成するための情報を設定。

	m_rbInfo.collider = &m_boxCollider;//剛体のコリジョンを設定する。

	m_rbInfo.mass = 0.0f;		//質量を0にすると動かない剛体になる。
	m_rbInfo.pos = m_position;
	m_rbInfo.rot = m_rotation;

	//剛体を作成。
	m_rigidBody.Create(m_rbInfo);
	//作成した剛体を物理ワールドに追加。
	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);


	////法線マップ
	/*D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/TILE5_N.tga",
		&m_normalMap);

	if (m_normalMap != NULL)
	{
		m_model.SetnormalMap(m_normalMap);
	}*/
}