#pragma once
#include "Indexbuffer.h"
#include "Vertexbuffer.h"
#include <d3d9.h>
class Primitive
{
public:
	Primitive();
	~Primitive();

	enum EType {
		eTriangleList,
		eTriangleStrip,
		eTypeNum,
	};

	void Create(
		EType					primitiveType,
		int						numVertex,
		int						vertexStride,
		const D3DVERTEXELEMENT9* vertexLayout,
		void*					pSrcVertexBuffer,
		int						numIndex,
		D3DFORMAT				indexFormat,
		void*					pSrcIndebuffer
	);

	void Release();

	/*!
	* @brief	頂点バッファの取得。
	*/
	Vertexbuffer* GetVertexBuffer()
	{
		return &m_vertexBuffer;
	}
	/*!
	* @brief	インデックスバッファの取得。
	*/
	Indexbuffer*  GetIndexBuffer()
	{
		return &m_indexBuffer;
	}
	/*!
	* @brief	D3DPRIMITIVETYPEを取得。
	*/
	D3DPRIMITIVETYPE GetD3DPrimitiveType() const
	{
		return m_d3dPrimitiveType;
	}
	/*!
	* @brief	頂点数を取得。
	*/
	int GetNumVertex() const
	{
		return m_numVertex;
	}
	/*!
	* @brief	ポリゴン数を取得。
	*/
	int GetNumPolygon() const
	{
		return m_numPolygon;
	}
	/*!
	* @brief	頂点定義を取得。
	*/
	IDirect3DVertexDeclaration9* GetVertexDecl()
	{
		return m_vertexBuffer.GetVertexDecl();
	}
private:
	int					m_numVertex;
	int					m_vertexStride;
	int					m_numIndex;
	int					m_numPolygon;
	Vertexbuffer		m_vertexBuffer;
	Indexbuffer			m_indexBuffer;
	EType				m_type;
	D3DPRIMITIVETYPE	m_d3dPrimitiveType;
};
