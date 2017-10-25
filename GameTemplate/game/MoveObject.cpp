#include "stdafx.h"
#include "MoveObject.h"

MoveObject::MoveObject()
{
}


MoveObject::~MoveObject()
{
	g_physicsWorld->RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	modelData.Release();
}

void MoveObject::Init(const char* modelName,D3DXVECTOR3	pos,D3DXQUATERNION	rot)
{

	//読み込むモデルのファイルパスを作成。
	char modelPath[256];
	sprintf(modelPath, "Assets/modelData/%s.x", /*locInfo.modelName*/modelName);
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
	position =pos;
	rotation =rot;

	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, {0.0f, 0.0, 0.0f, 1.0}, { 1.0f, 1.0f, 1.0f });
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
	rigidBody.GetBody()->setCollisionFlags( btCollisionObject::CF_CHARACTER_OBJECT);

	//作成した剛体を物理ワールドに追加。
	g_physicsWorld->AddRigidBody(&rigidBody);

	UMovelenge.x = position.x - 20.0f;
	LMovelenge.x = position.z - 2.0f;
	RMovelenge.x = position.z + 2.0f;
	DMovelenge.x = position.x;

}


void MoveObject::Update()
{
	D3DXVECTOR3 toPos;
	D3DXVECTOR3 LPos = position;
	D3DXVECTOR3 RPos = position;
	D3DXVECTOR3 UPos = position;
	D3DXVECTOR3 DPos = position;
	LPos.z -= 2.4f;
	RPos.z += 2.4f;
	UPos.x -= 2.4f;
	DPos.x += 2.4f;

	D3DXVec3Subtract(&toPos, &LPos, &game->GetPlayer()->Getpos());
	float Llen = D3DXVec3Length(&toPos);
	D3DXVec3Subtract(&toPos, &RPos, &game->GetPlayer()->Getpos());
	float Rlen = D3DXVec3Length(&toPos);
	D3DXVec3Subtract(&toPos, &DPos, &game->GetPlayer()->Getpos());
	float Dlen = D3DXVec3Length(&toPos);
	D3DXVec3Subtract(&toPos, &game->GetPlayer()->Getpos(), &UPos);
	float Ulen = D3DXVec3Length(&toPos);
	if (Llen < 1.5f&&position.z>LMovelenge.x)
	{
		Lflg = true;
	}
	else
	{
		Lflg = false;
	}

	if (Lflg)
	{
		position.z -= MoveSpeed;
		D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
		speed.z -= PAddSpeed;
		game->GetPlayer()->AddSpeed(speed);
	}

	if (Rlen < 1.5f&&position.z<RMovelenge.x)
	{
		Rflg = true;

	}
	else
	{
		Rflg = false;
	}

	if (Rflg)
	{
		position.z += MoveSpeed;
		D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
		speed.z += PAddSpeed;
		game->GetPlayer()->AddSpeed(speed);
	}

	if (Dlen < 1.0f&&position.x<DMovelenge.x)
	{
		Dflg = true;
	}
	else
	{
		Dflg = false;
	}

	if (Dflg)
	{
		position.x += MoveSpeed;
		D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
		speed.x += PAddSpeed;
		game->GetPlayer()->AddSpeed(speed);
	}

	if (Ulen < 1.0f&&position.x > UMovelenge.x)
	{
		Uflg = true;
	}
	else {
		Uflg = false;
	}

	if (Uflg)
	{
		//moveSpeed.x = 4.0f;
		position.x -= MoveSpeed;
		D3DXVECTOR3 speed = game->GetPlayer()->GetSpeed();
		speed.x -=PAddSpeed;
		game->GetPlayer()->AddSpeed(speed);
	}

	/*rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	btVector3 btPos;
	btPos.setX(position.x);
	btPos.setY(position.y);
	btPos.setZ(position.z);
	trans.setOrigin(btPos);
	btQuaternion btRot;
	btRot.setX(Rotation.x);
	btRot.setY(Rotation.y);
	btRot.setZ(Rotation.z);
	btRot.setW(Rotation.w);
	trans.setRotation(btRot);*/

	btTransform& Ttra = rigidBody.GetBody()->getWorldTransform();//剛体の移動処理
	Ttra.setOrigin({ position.x,position.y,position.z });
	Ttra.setRotation({ rotation.x,rotation.y,rotation.z,rotation.w });
	
	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f, });

}

void MoveObject::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix(), false,false);
}