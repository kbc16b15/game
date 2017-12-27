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


private:
	CRenderTarget	m_renderTarget;//シャドウマップを書きこむレンダリングターゲット
	D3DXMATRIX	m_lightViewMatrix;//ライトビューマトリクス。カメラ空間に変換
	D3DXMATRIX	m_lightProjectionMatrix;//ライトプロジェクションマトリクス。スクリーン空間に変換
	D3DXVECTOR3	m_viewPosition;//ライトビューの視点。
	D3DXVECTOR3 m_viewTarget;//ライトビューの注視点。
	//SkinModel	skinModel;
};

extern ShadowMap* g_shadowmap;

