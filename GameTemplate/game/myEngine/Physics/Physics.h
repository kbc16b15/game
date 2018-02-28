#pragma once


class RigidBody;

/*!
 * @brief	物理ワールド。
 */
class PhysicsWorld:public IGameObject
{
	//コンストラクタ
	PhysicsWorld();
	static PhysicsWorld* m_physicsWorld;//インスタンス
	btDefaultCollisionConfiguration*		collisionConfig;
	btCollisionDispatcher*					collisionDispatcher;	//!<衝突解決処理。
	btBroadphaseInterface*					overlappingPairCache;	//!<ブロードフェーズ。衝突判定の枝切り。
	btSequentialImpulseConstraintSolver*	constraintSolver;		//!<コンストレイントソルバー。拘束条件の解決処理。
	btDiscreteDynamicsWorld*				dynamicWorld;			//!<ワールド。
public:
//	PhysicsWorld();
	~PhysicsWorld();
	void Init();
	void Update() ;
	/*!
	* @brief	ダイナミックワールドを取得。
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	//インスタンスの生成
	static void PhysicsWorld::Create()
	{
		if (!m_physicsWorld)
		{
			m_physicsWorld = new PhysicsWorld;
		}

	}

	//インスタンスの消去
	static  void PhysicsWorld::Destroy()
	{
		delete m_physicsWorld;
		m_physicsWorld = nullptr;
	}
	//インスタンスの取得
	static PhysicsWorld& GetInstance()
	{
		return *m_physicsWorld;
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

//extern PhysicsWorld* g_physicsWorld;

