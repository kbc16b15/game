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

	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x",modelName);
	//���f�������[�h�B
	m_modelData.LoadModelData(modelPath, NULL);
	//���[�h�������f���f�[�^���g����SkinModel���������B
	m_model.Init(&m_modelData);
	//���C�g���������B
	m_light.SetAmbientLight(D3DXVECTOR4(0.8f, 0.8f, 0.8f, 1.0f));

	m_model.SetLight(&Game::GetInstance().GetLight());
	m_position =pos;
	m_rotation =rot;

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });

	//�L���[�u�}�b�v�̍쐬
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
