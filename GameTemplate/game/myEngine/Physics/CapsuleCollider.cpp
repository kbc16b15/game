/*!
 * @brief	�J�v�Z���R���C�_�[�B
 */

#include "stdafx.h"
#include "myEngine/Physics/CapsuleCollider.h"

/*!
 * @brief	�R���X�g���N�^�B
 */
CapsuleCollider::CapsuleCollider() :
	shape(nullptr)
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
CapsuleCollider::~CapsuleCollider()
{
	delete shape;
}
