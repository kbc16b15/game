/*!
 * @brief	キャラクタコントローラー。
 */

#pragma once

#include "myEngine/Physics/CapsuleCollider.h"
#include "myEngine/Physics/RigidBody.h"

/*!
	* @brief	キャラクタコントローラー。
	*/
class CharacterController{
public:
	CharacterController() {
		m_position = {0.0f, 0.0f, 0.0f};
		m_moveSpeed = {0.0f, 0.0f, 0.0f};
	}
	~CharacterController()
	{

	}
	/*!
		* @brief	初期化。
		*/
	void Init(float radius, float height, const D3DXVECTOR3& position);
	/*!
		* @brief	実行。
		*/
	void Execute();
	/*!
		* @brief	座標を取得。
		*/
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}
	/*!
		* @brief	座標を設定。
		*/
	void SetPosition(const D3DXVECTOR3& pos)
	{
		m_position = pos;
	}
	/*!
		* @brief	移動速度を設定。
		*/
	void SetMoveSpeed(const D3DXVECTOR3& speed )
	{
		m_moveSpeed = speed;
	}
	/*!
		* @brief	移動速度を取得。
		*/
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/*!
		* @brief	ジャンプさせる。
		*/
	void Jump( )
	{
		m_isJump = true;
		m_isOnGround = false;
	}
	/*!
		* @brief	ジャンプ中か判定
		*/
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	地面上にいるか判定。
	*/
	bool IsOnGround() const
	{
		return m_isOnGround;
	}
	/*!
	* @brief	コライダーを取得。
	*/
	CapsuleCollider* GetCollider()
	{
		return &m_collider;
	}
	/*!
	* @brief	重力を取得。
	*/
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}
	/*!
	* @brief	剛体を取得。
	*/
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	剛体を物理エンジンから削除。。
	*/
	void RemoveRigidBoby();
private:
	D3DXVECTOR3 		m_position;						//座標。
	D3DXVECTOR3 		m_moveSpeed ;					//移動速度。 
	bool 				m_isJump = false;				//ジャンプ中？
	bool				m_isOnGround = true;			//地面の上にいる？
	CapsuleCollider		m_collider;						//コライダー。
	float				m_radius = 0.0f;
	float				m_height = 0.0f;		
	RigidBody			m_rigidBody;					//剛体。
	float				m_gravity = -9.8f;				//重力。
};
