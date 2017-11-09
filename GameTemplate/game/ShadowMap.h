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
		return renderTarget.GetTexture();
	}
	//ライトビューの視点の設定
	void SetviewPosition(D3DXVECTOR3 viewPos)
	{
		viewPosition = viewPos;
	}
	//ライトビューの注視点の設定
	void SetviewTarget(D3DXVECTOR3 vTarget)
	{
		viewTarget = vTarget;
	}
	//ライトプロジェクション行列の取得
	D3DXMATRIX GetlightProjectionMatrix()
	{
		return lightProjectionMatrix;
	}
	//ライトビュー行列の取得
	D3DXMATRIX GetlightViewMatrix()
	{
		return lightViewMatrix;
	}


private:
	CRenderTarget	renderTarget;//シャドウマップを書きこむレンダリングターゲット
	D3DXMATRIX	lightViewMatrix;//ライトビューマトリクス。カメラ空間に変換
	D3DXMATRIX	lightProjectionMatrix;//ライトプロジェクションマトリクス。スクリーン空間に変換
	D3DXVECTOR3	viewPosition;//ライトビューの視点。
	D3DXVECTOR3 viewTarget;//ライトビューの注視点。
	//SkinModel	skinModel;
};

extern ShadowMap* g_shadowmap;

