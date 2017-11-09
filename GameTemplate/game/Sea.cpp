#include "stdafx.h"
#include "Sea.h"


Sea::Sea()
{
}


Sea::~Sea()
{
	modelData.Release();
}

void Sea::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{

	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x",modelName);
	//���f�������[�h�B
	modelData.LoadModelData(modelPath, NULL);
	//���[�h�������f���f�[�^���g����SkinModel���������B
	model.Init(&modelData);

	//���C�g���������B
	light.SetAmbientLight(D3DXVECTOR4(0.8f, 0.8f, 0.8f, 1.0f));

	model.SetLight(&light);
	position = pos;
	rotation = rot;

	model.UpdateWorldMatrix(position, rotation, { 1.0f, 1.0f, 1.0f });

	//�L���[�u�}�b�v�̍쐬
	/*D3DXCreateCubeTextureFromFile(g_pd3dDevice, "Assets/modelData/skyCubeMap.dds", &m_cubeTex);

	if (m_cubeTex != NULL)
	{
		model.SetcubeMap(m_cubeTex);
	}
	*/

	//D3DXCreateTextureFromFileA(g_pd3dDevice,
	//"Assets/modelData/NormalMap.png",
	//&normalMap);

	//if (normalMap != NULL)
	//{
	//	model.SetnormalMap(normalMap);
	//}
}

void Sea::Update()
{

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f, });

}

void Sea::Draw()
{

	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());

}