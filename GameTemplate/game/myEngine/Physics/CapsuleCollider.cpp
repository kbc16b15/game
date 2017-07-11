/*!
 * @brief	カプセルコライダー。
 */

#include "stdafx.h"
#include "myEngine/Physics/CapsuleCollider.h"

/*!
 * @brief	コンストラクタ。
 */
CapsuleCollider::CapsuleCollider() :
	shape(nullptr)
{
}
/*!
 * @brief	デストラクタ。
 */
CapsuleCollider::~CapsuleCollider()
{
	delete shape;
}
