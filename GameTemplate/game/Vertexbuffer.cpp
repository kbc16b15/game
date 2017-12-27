#include "stdafx.h"
#include "Vertexbuffer.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

Vertexbuffer::Vertexbuffer() :
	m_pVB(nullptr),
	m_stride(0),
	m_numVertex(0),
	m_size(0)
{

}


Vertexbuffer::~Vertexbuffer()
{
	Release();
}

void Vertexbuffer::Create(int numVertex, int stride, const D3DVERTEXELEMENT9* vertexLayout, const void* pSrcVertexBuffer)
{
	Release();
	m_numVertex = numVertex;
	m_stride = stride;
	m_size = m_numVertex*m_stride;
	HRESULT hr = g_pd3dDevice->CreateVertexBuffer(
		numVertex*stride,
		0,
		0,
		D3DPOOL_DEFAULT,
		&m_pVB,
		NULL
	);

	if (pSrcVertexBuffer != nullptr)
	{
		void* pDstVertexBuffer;
		hr = m_pVB->Lock(0, 0, &pDstVertexBuffer, D3DLOCK_DISCARD);

		memcpy(pDstVertexBuffer, pSrcVertexBuffer, m_size);
		m_pVB->Unlock();
	}

	g_pd3dDevice->CreateVertexDeclaration(vertexLayout, &m_pVertexDecl);
}

void Vertexbuffer::Release()
{
	if (m_pVB != nullptr) {
		m_pVB->Release();
		m_pVB = nullptr;
	}
}