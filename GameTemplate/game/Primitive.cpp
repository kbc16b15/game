#include "stdafx.h"
#include "Primitive.h"

Primitive *Primitive::m_primitive = NULL;

Primitive::Primitive() :
	m_numVertex(0),
	m_numIndex(0),
	m_vertexStride(0),
	m_type(eTriangleList),
	m_d3dPrimitiveType(D3DPT_TRIANGLELIST)
{

}


Primitive::~Primitive()
{
	Release();
}

void Primitive::Create(
	EType				primitiveType,
	int					numVertex,
	int					vertexStride,
	const D3DVERTEXELEMENT9* vertexLayout,
	void*				pSrcVertexBuffer,
	int					numIndex,
	D3DFORMAT			indexFormat,
	void*				pSrcIndexbuffer
	)
{
	m_type = primitiveType;
	m_numVertex = numVertex;
	m_vertexStride = vertexStride;
	m_numIndex = numIndex;
	Release();
	m_vertexBuffer.Create(numVertex, vertexStride, vertexLayout, pSrcVertexBuffer);
	m_indexBuffer.Create(numIndex, indexFormat, pSrcIndexbuffer);
	if (primitiveType == eTriangleList)
	{
		m_numPolygon = numIndex / 3;
		m_d3dPrimitiveType = D3DPT_TRIANGLELIST;
	}
	else if (primitiveType == eTriangleStrip)
	{
		m_numPolygon = numIndex - 2;
		m_d3dPrimitiveType = D3DPT_TRIANGLESTRIP;
	}
}

void Primitive::Release()
{
	m_vertexBuffer.Release();
	m_indexBuffer.Release();
}
