#pragma once
#include "HUD.h"
//#include "IGameObject.h"
class TitleScene :public IGameObject
{
public:
	//デストラクタ
	~TitleScene();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void PrePostDraw();
	//フェード
	void SceneFade();
	//スプライト生成関数
	HRESULT CreateSprite();
	//初回だけフェードインをなくす
	void SetStart(bool start)
	{
		m_isStart = start;
	}
	//インスタンスの取得
	static TitleScene& GetInstance()
	{
		return *m_title;
	}
	//インスタンスの生成
	static void TitleScene::Create()
	{
		if (!m_title)
		{
			m_title = new TitleScene;
		}
	
	}
	//インスタンスの消去
	static  void TitleScene::Destroy()
	{
		delete m_title;
		m_title = nullptr;
	}
private:
	
	//コンストラクタ
	TitleScene();
	static TitleScene* m_title;//インスタンス
	//ステート
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;			//フェード
	LPD3DXSPRITE		m_sprite;						//スプライト
	HUD*				m_titleHud;						//タイトル画像
	const D3DXVECTOR2	m_titlePos = { 595.0f,400.0f };	//タイトル画像の座標
	bool				m_isStart = false;
};

