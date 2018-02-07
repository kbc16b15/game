#pragma once
#include <d3dx9.h>


struct SMapChipLocInfo {
	const char* modelName;	//���f���B
	D3DXVECTOR3	pos;		//���W�B
	D3DXQUATERNION	rot;	//��]�B
};

SMapChipLocInfo Info1[] = {
#include "Boss.h"
};

SMapChipLocInfo Info2[] = {

#include "locationinfo7.h"
};