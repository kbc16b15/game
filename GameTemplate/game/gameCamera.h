#pragma once
#include "myEngine\HID\Pad.h"
class gameCamera
{
public:
	//コンストラクタ
	gameCamera();
	//デストラクタ
	~gameCamera();
	//初期化
	void Init();
	//更新
	void Update();
	//カメラの回転
	void RotCamera();

	//照準カメラ
	void RockCamera();
	//カメラの取得
	Camera Getcamera()
	{
		return m_camera;
	}
	//照準フラグ
	void SetRockCamera(bool Rcamera)
	{
		Rockonflg = Rcamera;
	}

private:
	Pad			pad;					//パッド
	Camera		m_camera;				//カメラ
	//D3DXVECTOR3 position;				//座標
	float		angleX = 0.0f;			//カメラ上下値
	D3DXVECTOR3	toCameraPos;			//カメラ座標
	float		angle = 0.0f;			//角度
	const float RotSpeedY = 2.0f;		//Y軸回転速度
	const float RotSpeedX = 1.0f;		//X軸回転速度
	const float CameraUpLimit = 20.0f;	//カメラ上下限度
	bool		Rockonflg = false;
	//bool	CameraTypeflg = false;

	D3DXVECTOR3 vec = { 0.0f,0.0f,0.0f };
};

