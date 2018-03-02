#pragma once
#include "stdafx.h"
struct SShapeVertex_PT {
	float	pos[4];
	float	uv[2];
};
static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
	{ 0,0,D3DDECLTYPE_FLOAT4	,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
	{ 0,16,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0 },
	D3DDECL_END()
};