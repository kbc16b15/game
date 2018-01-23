#include "stdafx.h"
#include "Spring.h"


Spring::Spring()
{
	scale = { 1.0f,1.0f,1.0f, };
}


Spring::~Spring()
{
	g_physicsWorld->RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	modelData.Release();
}

void Spring::Init(const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rot)
{
	//mapObject->Init(modelName, pos, rot);
	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.*/modelName);
	//モデルをロード。
	modelData.LoadModelData(modelPath, NULL);
	//ロードしたモデルデータを使ってSkinModelを初期化。
	model.Init(&modelData);

	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	model.SetLight(&light);
	position =/* locInfo.*/pos;
	rotation =/* locInfo.*/rot;

	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0, 0.0f, 1.0 }, { 1.0f, 1.0f, 1.0f });
	//ここから衝突判定絡みの初期化。
	//スキンモデルからメッシュコライダーを作成する。
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//続いて剛体を作成する。
	//まずは剛体を作成するための情報を設定。

	rbInfo.collider = &meshCollider;//剛体のコリジョンを設定する。
	rbInfo.mass = 0.0f;				//質量を0にすると動かない剛体になる。
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成。
	rigidBody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加。
	g_physicsWorld->AddRigidBody(&rigidBody);
	
}

void Spring::Update()
{
	D3DXVECTOR3 toPos=position;
	toPos.y += 1.0f;
	D3DXVec3Subtract(&toPos, &position, &g_game->GetPlayer()->Getpos());

	float len = D3DXVec3Length(&toPos);

	if (len <length)
	{
		Sflg = true;
		
	}
	else
	{
		/*Sflg = false;
		if (scale.y > 1.0f) { return; }
		scale.y += 0.03f;*/
	}

	if (Sflg)
	{
		/*D3DXVECTOR3 Ppos=g_game->GetPlayer()->Getpos();
		Ppos.y = position.y + 2.0f;
		g_game->GetPlayer()->Setpos({ position.x,position.y,position.z});
		g_game->GetPlayer()->SetJumpflg(true);*///プレイヤーをジャンプさせる処理




		if (scale.y < 0.0f) 
		{
			m_maxDownflg = true;//ボタンを押し切った
			//delete this;
			return; 
		}
		scale.y -= 0.003f;
		position.y -= 0.01f;
	}


	rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);
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
	trans.setRotation(btRot);

	//btTransform& Ttra = rigidBody.GetBody()->getWorldTransform();//剛体の移動処理
	//Ttra.setOrigin({ position.x,position.y,position.z });
	//Ttra.setRotation({ rotation.x,rotation.y,rotation.z,rotation.w });


	model.UpdateWorldMatrix(position, rotation, scale);

}

void Spring::Draw()
{
	model.Draw(&g_game->GetCamera()->GetViewMatrix(), &g_game->GetCamera()->GetProjectionMatrix());
}