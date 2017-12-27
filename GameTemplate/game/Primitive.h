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
	* @brief	���_�o�b�t�@�̎擾�B
	*/
	Vertexbuffer* GetVertexBuffer()
	{
		return &m_vertexBuffer;
	}
	/*!
	* @brief	�C���f�b�N�X�o�b�t�@�̎擾�B
	*/
	Indexbuffer*  GetIndexBuffer()
	{
		return &m_indexBuffer;
	}
	/*!
	* @brief	D3DPRIMITIVETYPE���擾�B
	*/
	D3DPRIMITIVETYPE GetD3DPrimitiveType() const
	{
		return m_d3dPrimitiveType;
	}
	/*!
	* @brief	���_�����擾�B
	*/
	int GetNumVertex() const
	{
		return m_numVertex;
	}
	/*!
	* @brief	�|���S�������擾�B
	*/
	int GetNumPolygon() const
	{
		return m_numPolygon;
	}
	/*!
	* @brief	���_��`���擾�B
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
