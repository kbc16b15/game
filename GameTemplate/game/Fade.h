#pragma once
class Fade:public IGameObject
{
public:

	~Fade();

	void Init();

	void Update();

	void PostDraw();

	//スプライト生成関数
	HRESULT CreateSprite();

	//フェード実行中フラグの取得
	bool isExecute()
	{
		return m_isExecute;
	}
	//!<フェードアウト。
	void StartFadeOut()
	{
		m_fadeSprite.SetAlpha(1.0f);
		m_timer = 0.0f;
		m_isActive = true;
		m_isExecute = true;
		m_state = eFadeOut;
	}
	//!<フェードイン。
	void StartFadeIn()
	{
		if (m_fadeSprite.GetAlpha() > 0)
		{
			m_timer = 0.0f;
			m_isActive = true;
			m_isExecute = true;
			m_state = eFadeIn;
		}
	}

	//インスタンスの生成
	static void Fade::Create()
	{
		if (!m_fade)
		{
			m_fade = new Fade;
		}

	}

	//インスタンスの消去
	static  void Fade::Destroy()
	{
		delete m_fade;
		m_fade = nullptr;
	}
	//インスタンスの取得
	static Fade& GetInstance()
	{
		return *m_fade;
	}
private:
	//コンストラクタ
	Fade();
	static Fade* m_fade;//インスタンス
private:
	
	enum EnState {
		eFadeOut,	//!<フェードアウト。
		eFadeIn		//!<フェードイン。
	};
	EnState				m_state = eFadeOut;				//フェードの状態
	float				m_timer=1.0f;					//タイマー
	float				m_outtimer = 0.0f;
	bool				m_isExecute = false;			//フェードを実行中
	Sprite				m_fadeSprite;					//!<背景のスプライト。
	Texture				m_fadeTex;						//!<背景のテクスチャ。
	const D3DXVECTOR2	m_fadepos = { 680.0f,300.0f };	//座標
	const D3DXVECTOR2	m_fadeScale = { 1300.0f,1200.0f };//拡大
	const float			FADE_TIME = 0.3f;				//フェード時間
	float				m_frameDeltaTime = 1.0f / 60.0f;//1フレームの時間
};
//extern Fade*   g_fade;

