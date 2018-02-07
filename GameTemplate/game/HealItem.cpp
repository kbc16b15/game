#include "stdafx.h"
#include "HealItem.h"
#include "Player.h"
#include "PlayerHp.h"

void HealItem::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
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
	m_light.SetAmbientLight(D3DXVECTOR4(6.8f, 0.8f, 0.8f, 1.0f));

	m_model.SetLight(&m_light);
	m_position =pos;
	m_rotation =rot;
}

void HealItem::Update()
{
	D3DXVECTOR3 toPos = m_position - Player::GetInstance().Getpos();
	float len = D3DXVec3Length(&toPos);
	if (len < 1.3f)
	{
		/*m_healSound = new Sound();
		m_healSound->Init("Assets/Sound/powerup03.wav");
		m_healSound->SetVolume(0.4f);
		m_healSound->Play(false);*/

		PlayerHp::GetInstance().PlayerHeal(1);
		m_healflg = true;
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 0.3f,0.3f,0.3f, });
}