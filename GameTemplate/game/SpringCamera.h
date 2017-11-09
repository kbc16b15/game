#pragma once
class SpringCamera
{
public:
	SpringCamera();
	~SpringCamera();

	//void* GetCamera()
	//{
	//	return &m_camera;
	//}

	//void Init(const CVector3& target, const CVector3& position, float maxMoveSpeed);
	///*!
	//* @brief	目標となる注視点を設定。
	//*/
	//void SetTarTarget(CVector3& target)
	//{
	//	m_target = target;
	//}
	///*!
	//* @brief	目標となる視点を設定。
	//*/
	//void SetTarPosition(CVector3 position)
	//{
	//	m_position = position;
	//}
//private:
//	Camera m_camera;
//
//	D3DXVECTOR3	m_target = {0.0f,0.0f,0.0f};		//!<目標となる注視点。
//	D3DXVECTOR3	m_position = { 0.0f,0.0f,0.0f };	//!<目標となる視点。
//	D3DXVECTOR3	m_targetMoveSpeed = { 0.0f,0.0f,0.0f };		//!<注視点の移動速度。
//	D3DXVECTOR3	m_positionMoveSpeed = { 0.0f,0.0f,0.0f };	//!<視点の移動速度。
//	float		m_maxMoveSpeed = 0.0f;					//!<最高移動速度。
//	float		m_targetDampingRate = 1.0f;				//!<減衰率。値が大きいほどカメラが遅れ付いてくる。
//	float		m_dampingRate = 1.0f;					//!<減衰率。
//	float		m_dampingRateVel = 0.0f;
};

