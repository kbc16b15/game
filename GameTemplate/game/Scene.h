#pragma once
#include "TitleScene.h"
#include "ResultScene.h"
#include "Fade.h"
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
	//シーンチェンジ
	void SceneChange();

	void SetScene(int SceneNo)
	{
		m_Scene = SceneNo;
	}
	enum SCENE
	{
		TITLE,			//タイトルシーン
		GAME,			//ゲームシーン
		GAME2,
		END,
		CHANGEGAME,		//ゲームシーンに遷移
		CHANGEGAME2,
		CHANGETITLE,	//タイトルシーンに遷移
		CHANGEEND,
	};
private:
	TitleScene* title=nullptr;	//タイトル
	ResultScene* end = nullptr;
	int m_Scene = TITLE;	//シーンの状態
};

extern Scene* scene;

