#pragma once
//#include "IGameObject.h"
#include "HUD.h"
class ClearScene :public IGameObject
{
public:
	//デストラクタ
	~ClearScene();
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

	//インスタンスの生成
	static  void ClearScene::Create()
	{
		if (!m_clear)
		{
			m_clear = new ClearScene;

		}
	}
	//インスタンスの消去
	static  void ClearScene::Destroy()
	{
		delete m_clear;
		m_clear = nullptr;
	}
	//インスタンスの取得
	static ClearScene& GetInstance()
	{
		return *m_clear;
	}
private:

	//コンストラクタ
	ClearScene();
	static ClearScene* m_clear;//インスタンス
								 //フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = Run;
	LPD3DXSPRITE		m_sprite;						//スプライト
	HUD					m_clearHud;							//タイトル画像
	const D3DXVECTOR2	m_clearHudPos = { 595.0f,400.0f };	//タイトル画像の座標
};

