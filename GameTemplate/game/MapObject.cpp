#include "stdafx.h"
#include "MapChip.h"
#include "MoveObject.h"
#include "TrapObject.h"
#include "FallObject.h"
#include "GoalObject.h"
#include "HealItem.h"
#include "Spring.h"
#include "BoxChip.h"
#include "myEngine\Physics\Physics.h"

MapObject::MapObject()
{
	m_scale = { 1.0f,1.0f,1.0f, };
}


MapObject::~MapObject()
{
	PhysicsWorld::GetInstance().RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
	m_modelData.Release();
}

void MapObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
	//���f�������[�h�B
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
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);

}

void MapObject::Update()
{
	m_model.UpdateWorldMatrix(m_position,m_rotation,m_scale);
}

void MapObject::Draw()
{
	m_model.SetReciveflg(true);

	m_model.Draw(&Camera::GetInstance().GetViewMatrix(), &Camera::GetInstance().GetProjectionMatrix());

}

MapObject* MapObject::MapReturn(const char* MapName)
{
	//�|�����[�t�B�Y�����g�����t�@�N�g���[
	//���ۃN���X�̃C���X�^���X���|�C���^�ō���āA�~�����}�b�v�̌^��Ԃ�
	MapObject* ob = nullptr;
	if (strcmp("MoveObject", MapName) == 0) {
		ob = new MoveObject();
	}
	else if (strcmp("BoxChip", MapName) == 0) {
		ob = new BoxChip();
	}
	else if (strcmp("TCircle", MapName) == 0) {
		ob = new TrapObject();
	}
	else if (strcmp("FCubeF", MapName) == 0) {
		ob = new FallObject(1);
	}
	else if (strcmp("FCubeB", MapName) == 0) {
		ob = new FallObject(2);
	}
	else if (strcmp("FCubeR", MapName) == 0) {
		ob = new FallObject(3);
	}
	else if (strcmp("FCubeL", MapName) == 0) {
		ob = new FallObject(4);
	}
	else if (strcmp("GoalObject", MapName) == 0) {
		ob = new GoalObject();
	}
	else if (strcmp("Boss", MapName) == 0) {
		//ob = new BoxChip();
	}
	else
	{
		ob = new MapChip();
	}
	return ob;
}