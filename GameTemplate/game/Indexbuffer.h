#pragma once
#include <d3d9.h>
class Indexbuffer
{
public:
	Indexbuffer();
	~Indexbuffer();

	void Create(int numIndex, D3DFORMAT format, const void* pSrcIndexBuffer);

	void Release();

	LPDIRECT3DINDEXBUFFER9 GetBody()
	{
		return m_pIB;
	}
private:
	LPDIRECT3DINDEXBUFFER9 m_pIB;
};


