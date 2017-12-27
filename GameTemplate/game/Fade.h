#pragma once
class Fade
{
public:
	Fade();
	~Fade();

	void Start();

	void Update();

	void Draw();

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
		m_timer = 0.0f;
		m_active = true;
		m_isExecute = true;
		m_state = eFadeOut;
	}
	//!<フェードイン。
	void StartFadeIn()
	{
		if (m_fadetex.Getalfa() > 0)
		{
			m_timer = 0.0f;
			m_active = true;
			m_isExecute = true;
			m_state = eFadeIn;
		}
	}
private:
	
	enum EnState {
		eFadeOut,	//!<フェードアウト。
		eFadeIn		//!<フェードイン。
	};
	HUD					m_fadetex;						//ブラックアウト用のスプライト。
	EnState				m_state = eFadeIn;				//フェードの状態
	float				m_timer=1.0f;					//タイマー
	float				m_outtimer = 0.0f;
	bool				m_isExecute = false;			//フェードを実行中
	bool				m_active = false;					//アクティブフラグ
	LPD3DXSPRITE		m_sprite;						//スプライト
	const D3DXVECTOR2	m_fadepos = { 700.0f,300.0f };	//座標
	const float			FADE_TIME = 0.1f;				//フェード時間
	float				m_frameDeltaTime = 1.0f / 60.0f;//1フレームの時間
};

extern Fade*   g_fade;

