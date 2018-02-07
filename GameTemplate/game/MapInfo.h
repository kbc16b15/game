#pragma once
#include <d3dx9.h>


struct SMapChipLocInfo {
	const char* modelName;	//モデル。
	D3DXVECTOR3	pos;		//座標。
	D3DXQUATERNION	rot;	//回転。
};

SMapChipLocInfo Info1[] = {
#include "Boss.h"
};

SMapChipLocInfo Info2[] = {

#include "locationinfo7.h"
};