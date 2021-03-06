#pragma once
class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
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

	int GetWidth() const
	{
		return m_width;
	}

	int GetHeight() const
	{
		return m_height;
	}

	//インスタンスの生成
	static void RenderTarget::MainRenderTargetCreate()
	{
		if (!m_mainRenderTarget)
		{
			m_mainRenderTarget = new RenderTarget;
		}

	}

	//インスタンスの取得
	static RenderTarget& MainRenderTargetGetInstance()
	{
		return *m_mainRenderTarget;
	}

	//インスタンスの消去
	static  void RenderTarget::Destroy()
	{
		delete m_mainRenderTarget;
		m_mainRenderTarget = nullptr;
	}
private:
	static RenderTarget* m_mainRenderTarget;//ポストエフェクト用のメインレンダリングターゲット
	LPDIRECT3DSURFACE9 m_surface;		//サーフェイス
	LPDIRECT3DTEXTURE9 m_texture;		//書き込み先のテクスチャ
	LPDIRECT3DSURFACE9 m_depthSurface;	//深度バッファ用のサーフェイス
	//IDirect3DTexture9* m_tex;
	int				m_width = 0;
	int				m_height = 0;
};

