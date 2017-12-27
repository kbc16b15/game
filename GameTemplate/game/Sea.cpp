#include "stdafx.h"
#include "Sea.h"


Sea::Sea()
{
}


Sea::~Sea()
{
	m_modelData.Release();
}

void Sea::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
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

	m_model.SetLight(&m_light);
	m_position = pos;
	m_rotation = rot;

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });

	//�L���[�u�}�b�v�̍쐬
	/*D3DXCreateCubeTextureFromFile(g_pd3dDevice, "Assets/modelData/skyCubeMap.dds", &m_cubeTex);

	if (m_cubeTex != NULL)
	{
		model.SetcubeMap(m_cubeTex);
	}
	*/

	D3DXCreateTextureFromFileA(g_pd3dDevice,
	"Assets/modelData/NormalMap.png",
	&m_normalMap);

	if (m_normalMap != NULL)
	{
		m_model.SetnormalMap(m_normalMap);
	}
}

void Sea::Update()
{

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f, });

}

void Sea::Draw()
{

	m_model.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());

}