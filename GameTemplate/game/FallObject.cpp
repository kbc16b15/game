#include "stdafx.h"
#include "FallObject.h"
#include "Player.h"
#include "myEngine\Physics\Physics.h"

FallObject::FallObject(int sType)
{
	RotDir = { 0.0f, 0.0f, 1.0f };
	m_speed = sType;
}

void FallObject::Init(const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	firstpos = pos;
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.modelName*/modelName);
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
	m_light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
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
	//rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	switch (m_speed)
	{
	case F:
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedF);
		break;
	case B:
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedB);
		break;
	case R:
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedR);
		break;
	case L:
		m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_AddSpeedL);
		break;
	default:
		break;
	}
	//�쐬�������̂𕨗����[���h�ɒǉ��B
	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);
}

void FallObject::Update()
{
	D3DXVECTOR3 Pspeed = Player::GetInstance().GetSpeed();
	D3DXVECTOR3 Ppos = Player::GetInstance().Getpos();
	D3DXVECTOR3 speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = NONE;
	m_speed = Player::GetInstance().GetDir();
	if (!Player::GetInstance().GetGround())
	{
		m_speed = NONE;
	}


	switch (m_speed)
	{
	case F:
		//if (Ppos.x<position.x + 1.8f&&Ppos.x>position.x - 1.8f){
			speed.y = Pspeed.y;
			speed.z = m_addSpeed;
			Player::GetInstance().AddSpeed(speed);
		//}
		break;
	case B:
		//if (Ppos.x<position.x + 1.8f&&Ppos.x>position.x - 1.8f){
			speed.y = Pspeed.y;
			speed.z = -m_addSpeed;
			Player::GetInstance().AddSpeed(speed);
		//}
		break;
	case R:
		//if (Ppos.z<position.z + 1.8f&&Ppos.z>position.z - 1.8f){
			speed.y = Pspeed.y;
			speed.x = m_addSpeed;
			Player::GetInstance().AddSpeed(speed);
		//}
		break;
	case L:
		//if (Ppos.z<position.z + 1.8f&&Ppos.z>position.z - 2.0f){
			speed.y = Pspeed.y;
			speed.x = -m_addSpeed;
			Player::GetInstance().AddSpeed(speed);
		//}
		//else if(Ppos.z>position.z+5.0f)
		//{
		//	speed.y = Pspeed.y;
		//	speed.z = -0.3f/*m_addSpeed*/;
		//	Player::GetInstance().AddSpeed(speed);
		//}
		//else if (Ppos.z<position.z-5.0f)
		//{
		//	speed.y = Pspeed.y;
		//	speed.z = -0.3f/*m_addSpeed*/;
		//	Player::GetInstance().AddSpeed(speed);
		//}
		break;
	
	default:


		break;
	} 

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f, });

}