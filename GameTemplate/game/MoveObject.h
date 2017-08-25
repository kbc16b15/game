#pragma once
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
//struct SMapChipLocInfo {
//	const char* modelName;		//���f���B
//	D3DXVECTOR3	pos;			//���W�B
//	D3DXQUATERNION	rotation;		//��]�B
//};
class MoveObject
{
public:
	MoveObject();
	~MoveObject();

	void Init(/*SMapChipLocInfo& locInfo*/const char* modelName, D3DXVECTOR3	pos, D3DXQUATERNION	rotation);
	void Update();
	void Draw();

	/*void SetMState(int mstate)
	{
		MState = mstate;
	}*/
private:

	bool Render = false;
	SkinModel model;
	SkinModelData modelData;
	D3DXVECTOR3	position;
	D3DXQUATERNION Rotation;
	D3DXVECTOR3			moveSpeed = { 0.0f,0.0f,0.0f };
	Light light;
	MeshCollider meshCollider;	//���b�V���R���C�_�[
	RigidBody rigidBody;		//���́B

	CharacterController	characterController;

	RigidBodyInfo rbInfo;

	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();

	D3DXVECTOR3 UMovelenge = position;
	D3DXVECTOR3 RMovelenge = position;
	D3DXVECTOR3 LMovelenge = position;
	D3DXVECTOR3 DMovelenge = position;

	bool		Rideflg = false;
};

