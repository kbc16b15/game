#pragma once
#include "Sound.h"
#include "IScene.h"
class Silhouette;
/*!
 * @brief	ゲームクラス。
 */
class Game:public IScene
{
public:
	//コンストラクタ
	Game();
	/*!
	 * @brief	デストラクタ。
	 */
	~Game();
	/*!
	 * @brief	起動関数。
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
	void StageClear(bool isClear)
	{
		m_isClear = isClear;
	}
	//BGMストップ
	void BgmStop()
	{
		if(m_bgmSound!=nullptr)
		m_bgmSound->Stop();
	}
	//ステージセット
	void SetStage(int No)
	{
		m_stageNo = No;
	}
private:
	//フェード
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	Silhouette*			m_silhouette = nullptr;
	EState				m_state = WaitFadeIn;		//フェードの状態
	Sound*				m_bgmSound=nullptr;			//サウンド
	const float			m_killZ = -10.0f;			//プレイヤーが死ぬ高さ
	bool				m_isNext = false;			//次のステージへ
	bool				m_isNextTo = false;			//次のステージ
	bool				m_isClear = false;			//クリア
	bool				m_isEnd = false;			//ゲームオーバー
	bool				m_isLoadEnd = false;
	int					m_stageNo=0;
};