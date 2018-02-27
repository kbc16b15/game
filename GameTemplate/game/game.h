#pragma once
#include "IGameObject.h"
#include "Sound.h"

/*!
 * @brief	ゲームクラス。
 */
class Game:public IGameObject
{
public:
	/*!
	 * @brief	デストラクタ。
	 */
	~Game();
	/*!
	 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
	 */
	void Init();
	/*!
	 * @brief	更新。
	 */
	void Update();
	/*!
	 * @brief	描画。
	 */
	void Draw();

	//シャドウの位置設定
	void SetShadow();

	//フェード
	void SceneFade();

	//ゲームシーンの開放
	void GameRelease();
	
	//ゲーム終了のフラグの取得
	bool GetGameEnd()
	{
		return m_isEnd;
	}
	//次のステージへ
	void StageNext()
	{
		m_isNext = true;
	}
	//クリア
	void StageClear()
	{
		m_isClear = true;
	}

	//インスタンスの生成
	static void Game::Create()
	{
		if (!m_game)
		{
			m_game = new Game;
		}

	}

	//インスタンスの取得
	static Game& GetInstance()
	{
		return *m_game;
	}

	//インスタンスの消去
	static  void Game::Destroy()
	{
		delete m_game;
		m_game = nullptr;
	}
private:
	
	//コンストラクタ
	Game();
	static Game* m_game;//インスタンス
private:
	//フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;		//フェードの状態
	Sound*				m_bgmSound=nullptr;			//サウンド
	const float			m_killZ = -10.0f;			//プレイヤーが死ぬ高さ
	bool				m_isNext = false;			//次のステージへ
	bool				m_isNextTo = false;			//次のステージ
	bool				m_isClear = false;			//クリア
	bool				m_isEnd = false;			//ゲームオーバー
	bool				m_isLoadEnd = false;
};