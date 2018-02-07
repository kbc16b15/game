#include "stdafx.h"
#include "Sky.h"

Sky::Sky()
{
}


Sky::~Sky()
{
	m_modelData.Release();
	if (m_cubeTex != NULL)
	{
		m_cubeTex->Release();
	}
}

void Sky::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{

	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x",modelName);
	//モデルをロード。
	m_modelData.LoadModelData(modelPath, NULL);
	//ロードしたモデルデータを使ってSkinModelを初期化。
	m_model.Init(&m_modelData);
	//ライトを初期化。
	m_light.SetAmbientLight(D3DXVECTOR4(0.8f, 0.8f, 0.8f, 1.0f));

	m_model.SetLight(&Game::GetInstance().GetLight());
	m_position =pos;
	m_rotation =rot;

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });

	//キューブマップの作成
	D3DXCreateCubeTextureFromFile(g_pd3dDevice, "Assets/modelData/pp.dds",&m_cubeTex);

	if (m_cubeTex != NULL)
	{
		m_model.SetcubeMap(m_cubeTex);
	}

}

void Sky::Update()
{
	
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f, });

}

void Sky::Draw()
{

	m_model.Draw(&Game::GetInstance().GetCamera()->GetViewMatrix(), &Game::GetInstance().GetCamera()->GetProjectionMatrix());
}
