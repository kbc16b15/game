#pragma once

class gameCamera:public IGameObject
{
public:

	//デストラクタ
	~gameCamera();
	//初期化
	void Init();
	//更新
	void Update();
	//カメラの回転
	void RotCamera();

	//追従カメラ
	void TrackingCamera();

	//照準カメラ
	void RockCamera();
	//ボス戦スタートカメラ　カメラ演出も入れる？
	void BossStartCamera();
	//ボス戦カメラ
	void BossCamera();
	//ボス戦エンドカメラ
	void BossEndCamera();
	//ボス固定カメラ
	void BossRockCamera();
	//照準フラグ
	void SetRockCamera(bool isRock)
	{
		m_isRockOn = isRock;
	}

	//インスタンスの生成
	static void gameCamera::Create()
	{
		if (!m_gameCamera)
		{
			m_gameCamera = new gameCamera;
		}

	}

	//インスタンスの消去
	static  void gameCamera::Destroy()
	{
		delete m_gameCamera;
		m_gameCamera = nullptr;
	}
	//インスタンスの取得
	static gameCamera& GetInstance()
	{
		return *m_gameCamera;
	}
private:
	//コンストラクタ
	gameCamera();
	static gameCamera* m_gameCamera;			//インスタンス
	D3DXVECTOR3		m_position;					//カメラ座標
	const float		m_rotSpeed = 2.0f;			//回転速度
	bool			m_isBossStartCamera = false;//ボス戦カメラ
	int				m_stateCameraTime = 250;	//開始カメラの時間
	bool			m_isBossEndCamera = false;	//ボス戦カメラ
	int				m_endCameraTime = 300;		//終了カメラの時間
	bool			m_isBossCamera = false;
	bool			m_isRockOn = false;
	//const float CameraUpLimit = 30.0f;		//カメラ上下限度
	//bool			m_istoCamera = false;			//カメラを操作中かどうか
	D3DXVECTOR3 vec = { 0.0f, 0.0f, 0.0f };


};