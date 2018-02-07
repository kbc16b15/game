#pragma once
#include "RenderTarget.h"

class ShadowMap
{
public:

	//コンストラクタ
	ShadowMap();
	//デストラクタ。
	~ShadowMap();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	//テクスチャの取得
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_renderTarget.GetTexture();
	}
	//ライトビューの視点の設定
	void SetviewPosition(D3DXVECTOR3 viewPos)
	{
		m_viewPosition = viewPos;
	}
	//ライトビューの注視点の設定
	void SetviewTarget(D3DXVECTOR3 vTarget)
	{
		m_viewTarget = vTarget;
	}
	//ライトプロジェクション行列の取得
	D3DXMATRIX GetlightProjectionMatrix()
	{
		return m_lightProjectionMatrix;
	}
	//ライトビュー行列の取得
	D3DXMATRIX GetlightViewMatrix()
	{
		return m_lightViewMatrix;
	}

	//インスタンスの生成
	static void ShadowMap::Create()
	{
		if (!m_shadowMap)
		{
			m_shadowMap = new ShadowMap;
		}
	}
	//インスタンスの消去
	static  void ShadowMap::Destroy()
	{
		delete m_shadowMap;
		m_shadowMap = nullptr;
	}
	//インスタンスの取得
	static ShadowMap& GetInstance()
	{
		return *m_shadowMap;
	}
private:
	

	static ShadowMap* m_shadowMap;//インスタンス
private:
	RenderTarget	m_renderTarget;//シャドウマップを書きこむレンダリングターゲット
	D3DXMATRIX	m_lightViewMatrix;//ライトビューマトリクス。カメラ空間に変換
	D3DXMATRIX	m_lightProjectionMatrix;//ライトプロジェクションマトリクス。スクリーン空間に変換
	D3DXVECTOR3	m_viewPosition;//ライトビューの視点。
	D3DXVECTOR3 m_viewTarget;//ライトビューの注視点。
};

//extern ShadowMap* g_shadowMap;

