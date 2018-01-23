#include "stdafx.h"
#include "CubeCollision.h"


CubeCollision::CubeCollision()
{
}


CubeCollision::~CubeCollision()
{
}


bool CubeCollision::Cube(D3DXVECTOR3 p1,D3DXVECTOR3 p2,float r1,float r2)
{

	float len = (((p2.x - p1.x)*(p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)) + ((p2.z - p1.z) * (p2.z - p1.z)));

	if (len <= ((r1 + r2) * (r1 + r2)))
	{
		return true;
	}
	return false;
}