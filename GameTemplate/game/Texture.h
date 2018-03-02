#pragma once
class Texture
{
public:
	Texture()
	{
	}
	~Texture()
	{
		Release();
	}
	void SetTextureDX(LPDIRECT3DTEXTURE9 tex)
	{
		if (tex != nullptr) {
			if (m_tex != nullptr) {
				m_tex->Release();
			}
			m_tex = tex;
			m_tex->AddRef();
			ComputeTexSize();
		}
	}

	LPDIRECT3DTEXTURE9 GetTextureDX() const
	{
		return m_tex;
	}
	//LPDIRECT3DCUBETEXTURE9 GetCubeMapDX() const
	//{
	//	return m_cubeTex;
	//}
	void Release()
	{
		if (m_tex) {
			m_tex->Release();
			m_tex = nullptr;
		}
		if (m_cubeTex) {
			m_cubeTex->Release();
			m_cubeTex = nullptr;
		}
	}
	//テクスチャの幅を取得。
	int GetWidth() const
	{
		return m_texW;
	}
	//テクスチャの高さを取得。
	int GetHeight() const
	{
		return m_texH;
	}
	bool IsCubeMap() const
	{
		return m_cubeTex != nullptr;
	}
	//テクスチャのロード
	bool Load(const char* fileName, bool isCubeMap = false);

private:
	//テクスチャのサイズを計算
	void ComputeTexSize()
	{
		D3DSURFACE_DESC desc;
		if (m_tex) {
			m_tex->GetLevelDesc(0, &desc);
		}
		else if (m_cubeTex) {
			m_cubeTex->GetLevelDesc(0, &desc);
		}
		m_texW = desc.Width;
		m_texH = desc.Height;
	}
	LPDIRECT3DTEXTURE9	m_tex = nullptr;		//!<テクスチャ。
	LPDIRECT3DCUBETEXTURE9 m_cubeTex = nullptr;	//!<キューブテクスチャ。
	int m_texW = 0;								//!<テクスチャの横幅。
	int m_texH = 0;								//!<テクスチャの縦幅。
};

