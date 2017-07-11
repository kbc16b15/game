/*!
 * @brief	エフェクトマネージャー
 */

#pragma once

class Effect;
/*!
 * @brief	エフェクトマネージャ。
 */
class EffectManager{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	EffectManager();
	/*!
	 * @brief	デストラクタ。
	 */
	~EffectManager();
	/*!
	 *@brief	エフェクトのロード。
	 *@details
	 * 読み込み済みのエフェクトの場合はロードは行われず、</br>
	 * 既存のエフェクトが返ってきます。
	 *@param[in]	filePath	ロードするエフェクトのファイルパス。
	 *@return	ロードしたエフェクトファイル。
	 */
	ID3DXEffect* LoadEffect( const char* filePath );
	/*!
	 * @brief	リリース。
	 */
	void Release();
private:
	std::map<int, ID3DXEffect*>		effectDictinary;	//!<CEffectのインスタンスのディクショナリ。ファイルパスのハッシュ値をキーに持ち、CEffectのインスタンスを値に持つ。
};
