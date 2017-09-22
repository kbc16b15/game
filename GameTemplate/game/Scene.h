#pragma once
#include "TitleScene.h"
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

	enum SCENE
	{
		TITLE,			//タイトルシーン
		GAME,			//ゲームシーン
		CHANGEGAME,		//ゲームシーンに遷移
		CHANGETITLE		//タイトルシーンに遷移
	};
private:
	TitleScene* title=nullptr;	//タイトル
	int m_Scene = TITLE;	//シーンの状態
};

extern Scene* scene;

