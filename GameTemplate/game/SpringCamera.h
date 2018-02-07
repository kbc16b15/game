#pragma once
#include "myEngine/Graphics/Camera.h"
class SpringCamera
{
public:

	~SpringCamera();

	//注視点
	//座標
	//移動最高速度
	void Init(const D3DXVECTOR3& target, const D3DXVECTOR3& position, float maxMoveSpeed);
	/*!
	* @brief	目標となる注視点を設定。
	*/
	void SetTarTarget(const D3DXVECTOR3& target)
	{
		m_target = target;
	}
	/*!
	* @brief	目標となる視点を設定。
	*/
	void SetTarPosition(const D3DXVECTOR3 position)
	{
		m_position = position;
	}
	/*!
	* @brief	注視点を設定。
	*/
	void SetTarget(const D3DXVECTOR3& target)
	{
		m_camera.SetLookatPt(target);
	}
	/*!
	* @brief	視点を設定。
	*/
	void SetPosition(const D3DXVECTOR3 position)
	{
		m_camera.SetEyePt(position);
	}
	/*!
	* @brief	遠平面を設定。
	*/
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}
	/*!
	* @brief	注視点を取得。
	*/
	const D3DXVECTOR3& GetTarget()
	{
		return m_camera.GetLookatPt();

	}
	/*!
	* @brief	視点を取得。
	*/
	const D3DXVECTOR3& GetPosition()
	{
		return m_camera.GetEyePt();
	}
	//プロジェクション行列のゲッター
	D3DXMATRIX GetProjectionMatrix()
	{
		return m_camera.GetProjectionMatrix();
	}
	//ビュー行列のゲッター
	D3DXMATRIX GetViewMatrix()
	{
		return m_camera.GetViewMatrix();
	}
	/*!
	* @brief	更新。
	*/
	void Update();
	/*!
	* @brief	カメラを取得。
	*/
	const Camera* GetCamera()
	{
		return &m_camera;
	}
	/*!
	* @brief	バネの減衰率を設定。
	*@detail
	* 値が大きいほどカメラが遅れて付いてきます。
	*/
	void SetDampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}
	/*!
	* @brief	カメラを取得。
	*/
	/*Camera* GetCamera()
	{
		return &m_camera;
	}*/
	/*void SetViewAngle(float angle)
	{
		m_camera.SetViewAngle(angle);
	}
	float GetViewAngle() const
	{
		return m_camera.GetViewAngle();
	}*/

	/*!
	* @brief	目標となる注視点を取得。
	*/
	const D3DXVECTOR3& GetTarTarget() const
	{
		return m_target;
	}
	/*!
	* @brief	目標となる視点を取得。
	*/
	const D3DXVECTOR3& GetTarPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	バネカメラ用のパラメータをクリア。
	*/
	void ClearSpringParame()
	{
		m_targetMoveSpeed = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_positionMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}

	void UpdateSpringCamera();

	//インスタンスの生成
	static void SpringCamera::Create()
	{
		if (!m_springCamera)
		{
			m_springCamera = new SpringCamera;
		}

	}

	//インスタンスの消去
	static  void SpringCamera::Destroy()
	{
		delete m_springCamera;
		m_springCamera = nullptr;
	}
	//インスタンスの取得
	static SpringCamera& GetInstance()
	{
		return *m_springCamera;
	}
private:
	SpringCamera();
	static SpringCamera* m_springCamera;
	Camera		m_camera;											//カメラ
	D3DXVECTOR3	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目標となる注視点
	D3DXVECTOR3	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目標となる視点
	D3DXVECTOR3	m_targetMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//注視点の移動速度
	D3DXVECTOR3	m_positionMoveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//視点の移動速度
	float		m_maxMoveSpeed = 0.0f;								//最高移動速度
	float		m_targetDampingRate = 1.0f;							//減衰率。値が大きいほどカメラが遅れ付いてくる
	float		m_dampingRate = 0.5f;								//減衰率
	
	float		m_dampingRateVel = 0.0f;
};

