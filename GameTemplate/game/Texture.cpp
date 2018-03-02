#include "stdafx.h"
#include "Texture.h"

bool Texture::Load(const char* fileName, bool isCubeMap)
{
	if (fileName == nullptr) {
		return false;
	}
	Release();
	if (!isCubeMap) {
		if (FAILED(D3DXCreateTextureFromFile(
			g_pd3dDevice,
			fileName,
			&m_tex))) {
			return false;
		}
	}
	else {
		if (FAILED(D3DXCreateCubeTextureFromFile(
			g_pd3dDevice,
			fileName,
			&m_cubeTex))) {
			return false;
		}
	}
	ComputeTexSize();
	return true;
}