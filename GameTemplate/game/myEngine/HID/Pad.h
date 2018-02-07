#pragma once
/*!
* @brief	ゲームパッドクラス。
*/
#pragma once

#include <XInput.h> // XInput API
#include "IGameObject.h"
/*!
*@brief	パッドステート。
*/
struct PAD_STATE
{
	XINPUT_STATE state;
	bool bConnected;
};
/*!
* @brief	ゲームパッドクラス。
*/
class Pad/*:public IGameObject*/
{
public:
	/*!
	* @brief	仮想ボタン定義。
	*/
	enum EnButton {
		enButtonUp,			//!<上。
		enButtonDown,		//!<下。
		enButtonLeft,		//!<左。
		enButtonRight,		//!<右。
		enButtonA,			//!<Aボタン。
		enButtonB,			//!<Bボタン。
		enButtonX,			//!<Xボタン。
		enButtonY,			//!<Yボタン。
		enButtonSelect,		//!<セレクトボタン。
		enButtonStart,		//!<スタートボタン。
		enButtonRB1,		//!<RB1ボタン。
		enButtonRB2,		//!<RB2ボタン。
		enButtonRB3,		//!<RB3ボタン。
		enButtonLB1,		//!<LB1ボタン。
		enButtonLB2,		//!<LB2ボタン。
		enButtonLB3,		//!<LB3ボタン。
		enButtonNum,		//!<ボタンの数。
	};
	/*!
	* @brief	デストラクタ。
	*/
	~Pad();
	/*!
	* @brief	初期化。
	*/
	//void Init();
	void Update();
	//void Draw();
	/*!
	*@brief	ボタンのトリガー判定。
	*@return	trueが返ってきたらトリガー入力。
	*/
	bool IsTrigger(EnButton button) const
	{
		return m_trigger[button] != 0;
	}
	/*!
	*@brief	ボタンが押されているか判定。
	*@return	trueが返ってきたら押されている。
	*/
	bool IsPress(EnButton button) const
	{
		return m_press[button] != 0;
	}
	/*!
	*@brief	左スティックのX軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetLStickXF() const
	{
		return m_lStickX;
	}
	/*!
	*@brief	左スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetLStickYF() const
	{
		return m_lStickY;
	}
	/*!
	*@brief	右スティックのX軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickXF() const
	{
		return m_rStickX;
	}
	/*!
	*@brief	右スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickYF() const
	{
		return m_rStickY;
	}

	//インスタンスの生成
	static  void Pad::Create()
	{
		if (!m_pad)
		{
			m_pad = new Pad;

		}
	}

	//インスタンスの消去
	static  void Pad::Destroy()
	{
		delete m_pad;
		m_pad = nullptr;
	}
	//インスタンスの取得
	static Pad& GetInstance()
	{
		return *m_pad;
	}
private:
	//コンストラクタ。
	Pad();

	static Pad*		m_pad;
	PAD_STATE	m_state;	//!<パッドステート。
	int m_padNo = 0;
	int m_trigger[enButtonNum];	//!<trigger入力のフラグ。
	int m_press[enButtonNum];	//!<press入力のフラグ。
	float m_lStickX;			//!<左スティックのX軸の入力量。
	float m_lStickY;			//!<左スティックのY軸の入力量。
	float m_rStickX;			//!<右スティックのX軸の入力量。
	float m_rStickY;			//!<右スティックのY軸の入力量。
};

