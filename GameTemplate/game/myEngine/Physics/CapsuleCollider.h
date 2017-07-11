/*!
 * @brief	�J�v�Z���R���C�_�[�B
 */

#pragma once

#include "myEngine/Physics/ICollider.h"

class CapsuleCollider : public ICollider
{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CapsuleCollider();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~CapsuleCollider();
	/*!
	* @brief	�쐬�B
	*/
	void Create(float radius, float height)
	{
		shape = new btCapsuleShape(radius, height);
	}
	btCollisionShape* GetBody() override
	{
		return shape;
	}
private:
	btCapsuleShape*		shape;
};
