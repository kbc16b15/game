#include "stdafx.h"
#include "BoxCollider.h"


BoxCollider::BoxCollider()
{
}


BoxCollider::~BoxCollider()
{
	delete m_boxShape;
}

void BoxCollider::Create(const D3DXVECTOR3& halfSize)
{
	btVector3 HalfSize;
	HalfSize.setX(halfSize.x);
	HalfSize.setY(halfSize.y);
	HalfSize.setZ(halfSize.z);

	m_boxShape = new btBoxShape(HalfSize);

}
