#include "stdafx.h"
#include "BoxChip.h"

//BoxChip::BoxChip()
//{
//}

void BoxChip::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
	//���f�������[�h�B
	//m_modelData.CloneModelData(m_modelData, NULL);
	m_modelData.LoadModelData(modelPath, NULL);
	//���[�h�������f���f�[�^���g����SkinModel���������B
	m_model.Init(&m_modelData);

	//���C�g�̃Z�b�g
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));
	//���C�g�J���[�̃Z�b�g
	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(0.7f, 0.7f, 0.7f, 1.0f));
	m_model.SetLight(&m_light);
	m_position = pos;
	m_rotation = rot;

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
	//�Փ˔��藍�݂̏������B
	m_boxCollider.Create({ 2.1f, 1.0f,2.1f });

	//���̂��쐬���邽�߂̏���ݒ�B

	m_rbInfo.collider = &m_boxCollider;//���̂̃R���W������ݒ肷��B

	m_rbInfo.mass = 0.0f;		//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
	m_rbInfo.pos = m_position;
	m_rbInfo.rot = m_rotation;

	//���̂��쐬�B
	m_rigidBody.Create(m_rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);


	////�@���}�b�v
	/*D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/TILE5_N.tga",
		&m_normalMap);

	if (m_normalMap != NULL)
	{
		m_model.SetnormalMap(m_normalMap);
	}*/
}