#pragma once
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/CapsuleCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
//#include "IGameObject.h"
//マップチップの配置情報。
//struct SMapChipLocInfo {
//	const char* modelName;		//モデル。
//	D3DXVECTOR3	pos;			//座標。
//	D3DXQUATERNION	rotation;		//回転。
//};
class Skelton;
class MapChip/*:public IGameObject*/
{
public:
	MapChip();
	~MapChip();
	void Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	void Update();
	void MoveObject();
	void Draw();
	bool Rend(bool Rendflg);


private:
	/*enum MapObjectState 
	{
		Normal,
		Move,

	};

	int MState = Normal;*/
	bool				Render = false;
	SkinModel			model;
	SkinModelData		modelData;
	D3DXVECTOR3			position;
	D3DXQUATERNION		rotation;
	D3DXVECTOR3			moveSpeed = { 0.0f,0.0f,0.0f };
	Light				light;
	MeshCollider		meshCollider;	//メッシュコライダー
	//CapsuleCollider	capsuleCollider; //カプセルコライダー
	RigidBody			rigidBody;		//剛体。

	CharacterController	characterController;

	RigidBodyInfo		rbInfo;

	D3DXMATRIX*			rootBoneMatrix = modelData.GetRootBoneWorldMatrix();

	//D3DXVECTOR3 UMovelenge = position;
	//D3DXVECTOR3 RMovelenge = position;
	//D3DXVECTOR3 LMovelenge = position;
	//D3DXVECTOR3 DMovelenge = position;

	//bool				Rideflg = false;

	Skelton*			skelton;
	int					jointNo;
};

