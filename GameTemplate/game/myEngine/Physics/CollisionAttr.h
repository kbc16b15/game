/*!
 * @brief	コリジョン属性
 */
#pragma once

/*!
 * @brief	コリジョン属性の大分類。
 */
enum EnCollisionAttr{
	enCollisionAttr_Ground,		
	enCollisionAttr_Character,	
	enCollisionAttr_Damage,
	//enCollisionAttr_ObjectHit,
	enCollisionAttr_AddSpeedR,
	enCollisionAttr_AddSpeedL,
	enCollisionAttr_AddSpeedF,
	enCollisionAttr_AddSpeedB,
	enCollisionAttr_User		//以下にユーザー定義のコリジョン属性を設定する。
};