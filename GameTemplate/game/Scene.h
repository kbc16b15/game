#pragma once
#include "TitleScene.h"
#include "ResultScene.h"
#include "Fade.h"
//#include "BaseScene.h"
class Scene
{
public:
	//コンストラクタ
	Scene();
	//デストラクタ
	~Scene();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Render();
	//シーン
	enum SCENE
	{
		TITLE,			//タイトルシーン
		GAME,			//ゲームシーン
		GAME2,
		END,
		CHANGEGAME,
		CHANGEGAME2,
		CHANGETITLE,
		CHANGEEND
	};

	//シーンチェンジ
	void SceneChange(SCENE SceneNo);

	//パッドの取得
	Pad GetPad()
	{
		return m_pad;
	}
private:
	TitleScene*		m_title=nullptr;	//タイトル
	ResultScene*	m_end = nullptr;	//リザルト
	SCENE			m_scene;			//シーンの状態
	Pad			m_pad;		//パッド
	//BaseScene*	m_bScene=nullptr;
};

extern Scene* g_scene;

