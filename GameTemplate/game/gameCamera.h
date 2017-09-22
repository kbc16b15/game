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
	//カメラの取得
	Camera Getcamera()
	{
		return m_camera;
	}
private:
	Pad			pad;			//パッド
	Camera		m_camera;		//カメラ
	D3DXVECTOR3 position;		//座標
	float		angleX = 0.0f;	//カメラ上下上限
	D3DXVECTOR3	toCameraPos;	//カメラ座標
	float angle = 0.0f;			//角度
	//bool	CameraTypeflg = false;
};

