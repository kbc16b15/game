#pragma once
//#include "IGameObject.h"
#include "IScene.h"
class ClearScene :public IScene
{
public:
	//コンストラクタ
	ClearScene();
	//デストラクタ
	~ClearScene();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void /*PrePost*/Draw();
	//フェード
	void SceneFade();
	
private:
	//フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = Run;
	Sprite				m_clearSprite;						//スプライト。
	Texture				m_clearTexture;						//背景のテクスチャ。
	const D3DXVECTOR2	m_clearPos = { 0.0f,0.0f };		//画像の座標
	const D3DXVECTOR2	m_clearScale = { 1300.0f,900.0f };//拡大
};

