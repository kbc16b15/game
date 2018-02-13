#pragma once

class ResultScene:public IGameObject
{
public:
	//デストラクタ
	~ResultScene();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	//フェード
	void SceneFade();
	//スプライト生成関数
	HRESULT CreateSprite();

	//インスタンスの生成
	static  void ResultScene::Create()
	{
		if (!m_result)
		{
			m_result = new ResultScene;

		}
	}
	//インスタンスの消去
	static  void ResultScene::Destroy()
	{
		delete m_result;
		m_result = nullptr;
	}
	//インスタンスの取得
	static ResultScene& GetInstance()
	{
		return *m_result;
	}
private:
	
	//コンストラクタ
	ResultScene();
	static ResultScene* m_result;//インスタンス
	//フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;
	LPD3DXSPRITE		m_sprite;						//スプライト
	HUD					m_resultHud;							//タイトル画像
	const D3DXVECTOR2	m_resultHudPos = { 700.0f,300.0f };	//タイトル画像の座標
};

