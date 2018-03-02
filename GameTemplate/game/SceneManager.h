#pragma once
#include "IScene.h"
#include "IGameObject.h"
class Game;
class SceneManager:public IGameObject
{

private:
	static SceneManager* m_sMgr;
	static IScene* m_pScene/*=nullptr*/; // シーンオブジェクト
	static Game* m_game/*=nullptr*/;
	static void ChangeState(IScene* scene); // シーンの遷移
	SceneManager();
	~SceneManager();
public:
	// シーン列挙型
	enum SCENE
	{
		TITLE,       // タイトル画面
		GAME,   // ゲームメイン画面
		GAME2,   // ゲームメイン画面2
		GAME3,   // ゲームメイン画面2
		RESULT,      // 結果画面
		CLEAR,		//クリアシーン
	};
	static void ChangeScene(SCENE scene); // シーンの遷移
	
	void PrePostDraw(); // シーンの描画
	void Update();


	//インスタンスの生成
	static void SceneManager::Create()
	{
		if (!m_sMgr)
		{
			m_sMgr = new SceneManager;
		}

	}

	//インスタンスの消去
	static void SceneManager::Destroy()
	{
		delete m_sMgr;
		m_sMgr = nullptr;
	}
	//インスタンスの取得
	static SceneManager& GetInstance()
	{
		return *m_sMgr;
	}
	//ゲームシーンの取得
	static Game& GetGame()
	{
		return *m_game;
	}
	//現在のシーンの取得
	static int GetScene()
	{
		return m_scene;
	}
private:
	static int m_scene;
};

