#pragma once
#include "IGameObject.h"
#include "HUD.h"
class SceneChange :
	public IGameObject
{
public:
	//デストラクタ
	~SceneChange();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void PrePostDraw();

	void SceneFade();

	void Change();
	int GetMapNo()
	{
		return m_stageNo;
	}

	void SetMapNo(int No)
	{
		m_stageNo = No;
	}

	void SetChange(bool Change)
	{
		m_isChange = Change;
	}

	bool GetChange()
	{
		return m_isChange;
	}

	//スプライト生成関数
	HRESULT CreateSprite();
	//インスタンスの取得
	static SceneChange& GetInstance()
	{
		return *m_change;
	}
	//インスタンスの生成
	static void SceneChange::Create()
	{
		if (!m_change)
		{
			m_change = new SceneChange;
		}

	}
	//インスタンスの消去
	static  void SceneChange::Destroy()
	{
		delete m_change;
		m_change = nullptr;
	}
private:

	//コンストラクタ
	SceneChange();
	static SceneChange* m_change;//インスタンス
	int m_stageNo = 0;
	bool m_isChange=false;

	//enum EState {
	//	WaitFadeIn,
	//	Run,
	//	WaitFadeOut
	//};
	//EState				m_state = WaitFadeIn;				//フェード
	LPD3DXSPRITE		m_sprite;							//スプライト
	HUD					m_changeHud;						//タイトル画像
	const D3DXVECTOR2	m_changePos = { 595.0f,400.0f };	//タイトル画像の座標
};

