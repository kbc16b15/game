#include "stdafx.h"
#include "MoveObject.h"
#include "Player.h"

void MoveObject::Init(const char* modelName,D3DXVECTOR3	pos,D3DXQUATERNION	rot)
{

	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬�B
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.modelName*/modelName);
	//���f�������[�h�B
	m_modelData.LoadModelData(modelPath, NULL);
	//���[�h�������f���f�[�^���g����SkinModel���������B
	m_model.Init(&m_modelData);

	m_model.SetLight(&m_light);
	m_position =pos;
	m_rotation =rot;

	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, {0.0f, 0.0, 0.0f, 1.0}, { 1.0f, 1.0f, 1.0f });
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
	m_rigidBody.GetBody()->setCollisionFlags( btCollisionObject::CF_CHARACTER_OBJECT);

	//�쐬�������̂𕨗����[���h�ɒǉ��B
	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);

	/*UMovelenge.x = position.x - 20.0f;
	LMovelenge.x = position.z - 2.0f;
	RMovelenge.x = position.z + 2.0f;
	DMovelenge.x = position.x;*/

}

void MoveObject::Update()
{
	//���[�u�I�u�W�F�N�g�̃C���X�^���X�̎擾
	/*std::vector<Spring*> springstl=Game::GetInstance().GetMap()->GetSpringObject();
	for (auto ss : springstl)
	{

		if (ss->Getmaxdown())
		{
			m_open1 = true;
		}

	}*/

	D3DXVECTOR3 toPos = m_position;
	D3DXVec3Subtract(&toPos, &m_position, &Player::GetInstance().Getpos());

	float len = D3DXVec3Length(&toPos);

	if (len <length)
	{
		m_open1 = true;

	}
	if (m_open1)
	{
		if (m_maxUp > m_position.y)
		{
			m_position.y += m_upSpeed;
			//m_maxUp�̒l�܂ŏグ��
		}
	}

	/*rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	btVector3 btPos;
	btPos.setX(position.x);
	btPos.setY(position.y);
	btPos.setZ(position.z);
	trans.setOrigin(btPos);
	btQuaternion btRot;
	btRot.setX(rotation.x);
	btRot.setY(rotation.y);
	btRot.setZ(rotation.z);
	btRot.setW(rotation.w);
	trans.setRotation(btRot);*/

	btTransform& Ttra = m_rigidBody.GetBody()->getWorldTransform();//���̂̈ړ�����
	Ttra.setOrigin({ m_position.x,m_position.y,m_position.z });
	Ttra.setRotation({ m_rotation.x,m_rotation.y,m_rotation.z,m_rotation.w });
	
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f, });

}

//void MoveObject::Draw()
//{
//	model.Draw(&SpringCamera::GetInstance().GetViewMatrix(), &SpringCamera::GetInstance().GetProjectionMatrix());
//}