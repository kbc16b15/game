#pragma once


class RigidBody;

/*!
 * @brief	�������[���h�B
 */
class PhysicsWorld
{
	btDefaultCollisionConfiguration*		collisionConfig;
	btCollisionDispatcher*					collisionDispatcher;	//!<�Փˉ��������B
	btBroadphaseInterface*					overlappingPairCache;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	btSequentialImpulseConstraintSolver*	constraintSolver;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	btDiscreteDynamicsWorld*				dynamicWorld;			//!<���[���h�B
public:
	PhysicsWorld();
	~PhysicsWorld();
	void Init();
	void Update() ;
	/*!
	* @brief	�_�C�i�~�b�N���[���h���擾�B
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	void AddRigidBody(RigidBody* rb);
	void RemoveRigidBody(RigidBody* rb);
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
		)
	{
		dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
};

extern PhysicsWorld* g_physicsWorld;

