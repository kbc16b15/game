#include "stdafx.h"
#include "TrapObject.h"

void TrapObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	m_rotDir = { 0.0f,1.0f,0.0f };
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", modelName);
	//���f�������[�h�B
	//if (g_load){
	m_modelData.LoadModelData(modelPath, NULL);
	//	m_modelData.CloneModelData(m_modelData, NULL);
	/*}
	else{
		
		g_load = true;
	}*/
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

	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
	//��������Փ˔��藍�݂̏������B
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����B
	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);
	//�����č��̂��쐬����B
	//�܂��͍��̂��쐬���邽�߂̏���ݒ�B

	m_rbInfo.collider = &m_meshCollider;//���̂̃R���W������ݒ肷��B
	m_rbInfo.mass = 0.0f;				//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
	m_rbInfo.pos = m_position;
	m_rbInfo.rot = m_rotation;
	//���̂��쐬�B
	m_rigidBody.Create(m_rbInfo);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Damage);
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);

	m_model.SetSpecularlight(true);
}


void TrapObject::Update()
{
	Rot();
	//���̂̈ړ�����	
	btTransform& Ttra = m_rigidBody.GetBody()->getWorldTransform();
	Ttra.setOrigin({ m_position.x,m_position.y,m_position.z });
	Ttra.setRotation({ m_rotation.x,m_rotation.y,m_rotation.z,m_rotation.w });
	
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void TrapObject::Rot()
{
	m_angle += m_rotSpeed;
	D3DXQuaternionRotationAxis(&m_rotation, &m_rotDir, m_angle);//�I�u�W�F�N�g�������܂����ɂȂ�H
}