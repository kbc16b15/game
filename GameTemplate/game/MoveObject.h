#pragma once
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
//struct SMapChipLocInfo {
//	const char* modelName;		//モデル。
//	D3DXVECTOR3	pos;			//座標。
//	D3DXQUATERNION	rotation;		//回転。
//};
class MoveObject
{
public:
	MoveObject();
	~MoveObject();
	void Start();
	void Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3 pos, D3DXQUATERNION rotation);
	void Update();
	void Draw();

	/*void SetMState(int mstate)
	{
		MState = mstate;
	}*/
	D3DXVECTOR3 Getpos()
	{
		return position;

	}
	bool GetRide()
	{
		return Rideflg;
	}


private:

	bool			Render = false;
	SkinModel		model;
	SkinModelData	modelData;
	D3DXVECTOR3		position;
	D3DXQUATERNION	Rotation;
	D3DXVECTOR3		moveSpeed = { 0.0f,0.0f,0.0f };
	Light			light;
	MeshCollider	meshCollider;	//メッシュコライダー
	RigidBody		rigidBody;		//剛体。	
	CharacterController	characterController;

	RigidBodyInfo	rbInfo;
	D3DXVECTOR3		UMovelenge = position;
	/*D3DXVECTOR3	RMovelenge = position;
	D3DXVECTOR3		LMovelenge = position;
	D3DXVECTOR3		DMovelenge = position;*/

	bool			Rideflg = false;

};

