#pragma once
class CRenderTarget
{
public:
	CRenderTarget();
	~CRenderTarget();
	void Release();
	void Create(
		int w,
		int h,
		int mipLevel,
		D3DFORMAT colorFormat,
		D3DFORMAT depthStencilFormat,
		D3DMULTISAMPLE_TYPE multiSampleType,
		int multiSampleQuality);
	//レンダリングターゲットを取得
	LPDIRECT3DSURFACE9 GetRenderTarget()
	{
		return m_surface;
	}
	//デプスステンシルバッファの取得
	LPDIRECT3DSURFACE9 GetDepthStencilBuffer()
	{
		return m_depthSurface;
	}
	//テクスチャ取得
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_texture;
	}
private:
	LPDIRECT3DSURFACE9 m_surface;		//サーフェイス
	LPDIRECT3DTEXTURE9 m_texture;		//書き込み先のテクスチャ
	LPDIRECT3DSURFACE9 m_depthSurface;	//深度バッファ用のサーフェイス
	//IDirect3DTexture9* m_tex;
};

