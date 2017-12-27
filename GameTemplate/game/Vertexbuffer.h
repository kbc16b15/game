#pragma once
#include <d3d9.h>
enum EVertexFormat {
	eVertexFormat_xyz = D3DFVF_XYZ,
	eVertexFormat_wyzrhw = D3DFVF_XYZRHW,
	eVertexFormat_xyzw = D3DFVF_XYZW,
	eVertexFormat_normal = D3DFVF_NORMAL,
	eVertexFormat_diffuse = D3DFVF_DIFFUSE,
	eVertexFormat_tex0 = D3DFVF_TEX0,
	eVertexFormat_tex1 = D3DFVF_TEX1,
	eVertexFormat_tex2 = D3DFVF_TEX2,
	eVertexFormat_tex3 = D3DFVF_TEX3,
	eVertexFormat_tex4 = D3DFVF_TEX4,
	eVertexFormat_tex5 = D3DFVF_TEX5,
	eVertexFormat_tex6 = D3DFVF_TEX6,
	eVertexFormat_tex7 = D3DFVF_TEX7,
	eVertexFormat_tex8 = D3DFVF_TEX8,
	eVertexFormat_invalid = 0xffffffff,

};

//頂点バッファ
class Vertexbuffer
{
public:
	Vertexbuffer();
	~Vertexbuffer();

	void Create(
		int numVertex,
		int stride,
		const D3DVERTEXELEMENT9* vertexLayout,
		const void* pSrcVertexBuffer

	);

	void Release();

	LPDIRECT3DVERTEXBUFFER9 GetBody()
	{
		return m_pVB;
	}


	int GetStride() const
	{
		return m_stride;
	}

	IDirect3DVertexDeclaration9* GetVertexDecl()
	{
		return m_pVertexDecl;
	}
private:
	LPDIRECT3DVERTEXBUFFER9			m_pVB;
	IDirect3DVertexDeclaration9*	m_pVertexDecl;
	int								m_stride;
	int								m_numVertex;
	int								m_size;
};



