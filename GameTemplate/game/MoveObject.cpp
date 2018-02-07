#include "stdafx.h"
#include "MoveObject.h"
#include "Player.h"

void MoveObject::Init(const char* modelName,D3DXVECTOR3	pos,D3DXQUATERNION	rot)
{

	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.modelName*/modelName);
	//モデルをロード。
	m_modelData.LoadModelData(modelPath, NULL);
	//ロードしたモデルデータを使ってSkinModelを初期化。
	m_model.Init(&m_modelData);

	m_model.SetLight(&m_light);
	m_position =pos;
	m_rotation =rot;

	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, {0.0f, 0.0, 0.0f, 1.0}, { 1.0f, 1.0f, 1.0f });
	//ここから衝突判定絡みの初期化。
	//スキンモデルからメッシュコライダーを作成する。
	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);
	//続いて剛体を作成する。
	//まずは剛体を作成するための情報を設定。
	
	m_rbInfo.collider = &m_meshCollider;//剛体のコリジョンを設定する。
	m_rbInfo.mass = 0.0f;				//質量を0にすると動かない剛体になる。
	m_rbInfo.pos = m_position;
	m_rbInfo.rot = m_rotation;
	//剛体を作成。
	m_rigidBody.Create(m_rbInfo);
	m_rigidBody.GetBody()->setCollisionFlags( btCollisionObject::CF_CHARACTER_OBJECT);

	//作成した剛体を物理ワールドに追加。
	PhysicsWorld::GetInstance().AddRigidBody(&m_rigidBody);

	/*UMovelenge.x = position.x - 20.0f;
	LMovelenge.x = position.z - 2.0f;
	RMovelenge.x = position.z + 2.0f;
	DMovelenge.x = position.x;*/

}

void MoveObject::Update()
{
	//ムーブオブジェクトのインスタンスの取得
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
			//m_maxUpの値まで上げる
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

	btTransform& Ttra = m_rigidBody.GetBody()->getWorldTransform();//剛体の移動処理
	Ttra.setOrigin({ m_position.x,m_position.y,m_position.z });
	Ttra.setRotation({ m_rotation.x,m_rotation.y,m_rotation.z,m_rotation.w });
	
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f, });

}

//void MoveObject::Draw()
//{
//	model.Draw(&SpringCamera::GetInstance().GetViewMatrix(), &SpringCamera::GetInstance().GetProjectionMatrix());
//}