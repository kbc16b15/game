#include "stdafx.h"
#include "MapChip.h"



MapChip::MapChip()
{

}
	//position(0.0f, 0.0f, 0.0f),
	//rotation(0.0f, 0.0f, 0.0f, 1.0f)



MapChip::~MapChip()
{
	g_physicsWorld->RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
	m_modelData.Release();
	
}
void MapChip::Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	//mapObject->Init(modelName, pos, rot);
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
	//���f�������[�h�B
	m_modelData.LoadModelData(modelPath, NULL);
	//���[�h�������f���f�[�^���g����SkinModel���������B
	m_model.Init(&m_modelData);

	//���C�g���������B
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));

	m_model.SetLight(&m_light);
	m_position =pos;
	m_rotation =rot;

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
	//��������Փ˔��藍�݂̏������B
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);
	//�����č��̂��쐬����B
	//�܂��͍��̂��쐬���邽�߂̏���ݒ�B

	m_rbInfo.collider = &m_meshCollider;//���̂̃R���W������ݒ肷��B
	m_rbInfo.mass = 0.0f;				//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
	m_rbInfo.pos = {0.0f, 0.0f, 0.0f};
	m_rbInfo.rot = {0.0f, 0.0f, 0.0f, 1.0f};
	//���̂��쐬�B
	m_rigidBody.Create(m_rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	g_physicsWorld->AddRigidBody(&m_rigidBody);


}

void MapChip::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f, });
}

void MapChip::Draw()
{
	m_model.SetReciveflg(true);
	
	m_model.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());

}

//bool MapChip::Rend(bool Rendflg)
//{
//	if (Rendflg)
//	{
//		Render = true;
//		
//	}
//	return Render;
//}