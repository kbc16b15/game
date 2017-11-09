#include "stdafx.h"
#include "HealItem.h"


HealItem::HealItem()
{
}


HealItem::~HealItem()
{
	//g_physicsWorld->RemoveRigidBody(&rigidBody);
	//rigidBody.Release();
	modelData.Release();
}

void HealItem::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
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
	position =pos;
	rotation =rot;
}

void HealItem::Update()
{
	D3DXVECTOR3 toPos = position - game->GetPlayer()->Getpos();
	float len = D3DXVec3Length(&toPos);
	if (len < 0.8f)
	{
		m_HealSound = new Sound();
		m_HealSound->Init("Assets/Sound/powerup03.wav");
		m_HealSound->SetVolume(0.4f);
		m_HealSound->Play(false);


		game->Heal(1);
		Healflg = true;
	}

	model.UpdateWorldMatrix(position, rotation, { 0.3f,0.3f,0.3f, });
}

void HealItem::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
