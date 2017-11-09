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

	enum SCENE
	{
		TITLE,			//タイトルシーン
		GAME,			//ゲームシーン
		//GAME2,
		END,
		CHANGEGAME,
		//CHANGEGAME2,
		CHANGETITLE,
		CHANGEEND
	};

	//シーンチェンジ
	void SceneChange(SCENE SceneNo);

private:
	TitleScene* title=nullptr;
	ResultScene* end = nullptr;
	//BaseScene* m_bScene=nullptr;
	SCENE m_Scene;
};

extern Scene* scene;

