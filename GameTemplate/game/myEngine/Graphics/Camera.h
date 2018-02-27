#pragma once

/*!
 *@brief	カメラクラス。
 */

class Camera {
private:
	static Camera*			m_camera;
	D3DXMATRIX				m_viewMatrix;			//!<ビュー行列。カメラ行列とも言う。
	D3DXMATRIX				m_projectionMatrix;		//!<プロジェクション行列。ビュー空間から射影空間に変換する行列。
	D3DXMATRIX				m_viewMatrixInv;		//カメラ行列の逆行列
	D3DXMATRIX				m_rotationMatrix;		//回転行列
	D3DXVECTOR3				m_vEyePt;				//!<カメラクラスを作るためのヒント。カメラの視点。この辺りはメンバ変数に変更する。
	D3DXVECTOR3				m_vLookatPt;			//!<カメラクラスを作るためのヒント。カメラの注視点。どこを見ているかという情報。この辺りはメンバ変数に変更する。
	D3DXVECTOR3				m_vUpVec;				//!<カメラクラスを作るためのヒント。カメラの上方向。基本的にY方向でかまわない。基本的には・・・。この辺りはメンバ変数に変更する。
	float					m_far;					//!<遠平面。
	float					m_near;					//!<近平面。
	float					m_aspect;				//!<アスペクト比
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	Camera();
	/*!
	 *@brief	デストラクタ
	 */
	~Camera();
	/*!
	 *@brief	アスペクト比を設定。
	 */
	void SetAspect(float _aspect);
	/*!
	 *@brief	アスペクト比を取得。
	 */
	float GetAspect();
	/*!
	 *@brief	ファーを設定。
	 */
	void SetFar(float _far);
	/*!
	 *@brief	ニアを取得。
	 */
	float GetNear();
	/*!
	 *@brief	ファーを取得。
	 */
	float GetFar();
	/*!
	 *@brief	ニアを設定。
	 */
	void SetNear(float _near);
	/*!
	 *@brief	視点を設定。
	 */
	void SetEyePt(D3DXVECTOR3 pt);
	/*!
	 *@brief	視点を取得。
	 */
	D3DXVECTOR3 GetEyePt();
	/*!
	 *@brief	注視点を設定。
	 */
	void SetLookatPt(D3DXVECTOR3 pt);
	/*!
	 *@brief	注視点の取得。
	 */
	D3DXVECTOR3 GetLookatPt();
	/*!
	 *@brief	上方向の設定。
	 */
	void SetUpVec(D3DXVECTOR3 up);
	/*!
	 *@brief	上方向の取得。
	 */
	D3DXVECTOR3 GetUpVec();
	/*!
	 *@brief	ビュー行列の設定。
	 */
	void SetViewMatrix(D3DXMATRIX mView);
	/*!
	 *@brief	ビュー行列の取得。
	 */
	D3DXMATRIX GetViewMatrix();
	/*!
	 *@brief	プロジェクション行列の設定。
	 */
	void SetProjectionMatrix(D3DXMATRIX mProj);
	/*!
	 *@brief	プロジェクション行列の取得。
	 */
	D3DXMATRIX GetProjectionMatrix();
	/*!
	 *@brief	カメラの更新処理。
	 */
	void Update();
	/*!
	 *@brief	カメラの初期化。
	 */
	void Init();

	//カメラの回転行列を取得。
	const D3DXMATRIX& GetCameraRotation() const
	{
		return m_rotationMatrix;
	}

	//ビュー行列の逆行列を取得。
	
	const D3DXMATRIX& GetViewMatrixInv() const
	{
		return m_viewMatrixInv;
	}

	//インスタンスの生成
	static void Camera::Create()
	{
		if (!m_camera)
		{
			m_camera = new Camera;
		}
	}

	//インスタンスの消去
	static  void Camera::Destroy()
	{
		delete m_camera;
		m_camera = nullptr;
	}
	//インスタンスの取得
	static Camera& GetInstance()
	{
		return *m_camera;
	}

};