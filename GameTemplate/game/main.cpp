/*!
*@brief	ゲームテンプレート。
*/
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Scene.h"
#include "Fade.h"
#include "ShadowMap.h"
#include "Primitive.h"
#include "RenderTarget.h"


LPD3DXEFFECT copyEffect;
LPD3DXEFFECT monochromeEffect;		//!<18-4 モノクロフィルターをかけるシェーダー。
Primitive*			m_primitive;				//プリミティブ

Game* g_game=nullptr;
Scene* g_scene=nullptr;
Fade* g_fade = nullptr;
ShadowMap* g_shadowmap= nullptr;
CRenderTarget*		g_renderTarget;				//ポストエフェクト用のレンダリングターゲット？2


void InitMainRenderTarget()
{
	//18-2 メインレンダリングターゲットを作成する。
	g_renderTarget = new CRenderTarget;
	g_renderTarget->Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D16,				//デプスステンシルバッファのフォーマット。一般的に16bitと24bitフォーマットが使われることが多い。今回は24bitフォーマットを使う。

		D3DMULTISAMPLE_NONE,
		0
	);
}

void DrawQuadPrimitive()
{
	// 頂点ストリーム0番に板ポリの頂点バッファを設定する。
	g_pd3dDevice->SetStreamSource(
		0,												//頂点ストリームの番号。
		m_primitive->GetVertexBuffer()->GetBody(),		//頂点バッファ。
		0,												//頂点バッファの読み込みを開始するオフセットのバイト数。
														//今回は先頭から読み込むので0でいい。
		m_primitive->GetVertexBuffer()->GetStride()		//頂点一つ分のサイズ。単位はバイト。
	);
	// インデックスバッファを設定。
	g_pd3dDevice->SetIndices(m_primitive->GetIndexBuffer()->GetBody());
	// 頂点定義を設定する。
	g_pd3dDevice->SetVertexDeclaration(m_primitive->GetVertexDecl());
	//　準備が整ったので描画。
	g_pd3dDevice->DrawIndexedPrimitive(
		m_primitive->GetD3DPrimitiveType(),	//プリミティブの種類を指定する。
		0,										//ベース頂点インデックス。0でいい。
		0,										//最小の頂点インデックス。0でいい。
		m_primitive->GetNumVertex(),			//頂点の数。
		0,										//開始インデックス。0でいい。
		m_primitive->GetNumPolygon()			//プリミティブの数。
	);
}

void InitQuadPrimitive()
{
	m_primitive = new Primitive;
	//頂点の構造体。
	struct SVertex {
		float pos[4];	//頂点座標。
		float uv[2];	//UV座標。
	};
	//頂点バッファ。
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};

	//頂点レイアウト。頂点バッファの構造がどのようになっているかをGPUに教えるためのもの。
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//頂点ストリームの0番目の0バイト目からfloat型の4つ分のデータは座標(D3DDECLUSAGE_POSITION)であることを示している。
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		//頂点ストリームの0番目の16バイト目からfloat型の2つ分のデータはUV座標(D3DDECLUSAGE_TEXCOORD)であることを示している。
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};
	//インデックスバッファ。
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	m_primitive->Create(
		Primitive::eTriangleStrip,	//今回はプリミティブの種類はトライアングルストリップ。
		4,							//頂点の数。四角形の板ポリでトライアングルストリップなので４。
		sizeof(SVertex),			//頂点ストライド。一つの頂点の大きさ。単位はバイト。
		scShapeVertex_PT_Element,	//頂点レイアウト。
		vertexBuffer,				//頂点バッファ。
		4,							//インデックスの数。
		D3DFMT_INDEX16,				//インデックスバッファのフォーマット。今回は16bitフォーマットを指定する。
									//インデックスの数が65536以下の場合は16bitでいいが、それを超える場合はD3DFMT_INDEX32を指定する。
		indexBuffer					//インデックスバッファ。
	);
}

void LoadShaders()
{
	// ハンズオン 4
	LPD3DXBUFFER compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/Copy.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif 
		NULL,
		&copyEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}

//	hr = D3DXCreateEffectFromFile(
//		g_pd3dDevice,
//		"Assets/Shader/MonochromeFilter.fx",
//		NULL,
//		NULL,
//#ifdef _DEBUG
//		D3DXSHADER_DEBUG,
//#else
//		D3DXSHADER_SKIPVALIDATION,
//#endif // _DEBUG
//		NULL,
//		&monochromeEffect,
//		&compileErrorBuffer
//	);
//
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
//		std::abort();
//	}
}

void CopyMainRTToCurrentRT()
{
	// Zテストで失敗してもらったら困るので、Zテストは無効にしておく。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// αブレンドもいらない。
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	LPD3DXEFFECT shader = copyEffect;			//18-3 コピーを行うシェーダーを使う場合はこちら。
												//LPD3DXEFFECT shader = monochromeEffect;		//18-4 モノクロフィルターをかける場合はこちらを使用する。
												//シェーダーを設定。
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//シーンテクスチャを設定する
	shader->SetTexture("g_tex", g_renderTarget->GetTexture());
	//定数レジスタへの変更をコミットする。
	shader->CommitChanges();
	DrawQuadPrimitive();
	shader->EndPass();
	shader->End();
	// 変更したレンダリングステートを元に戻す。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}
//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	InitMainRenderTarget();
	//18-3 四角形の板ポリプリミティブを作成。
	InitQuadPrimitive();
	//18-3、18-4 シェーダーをロード。
	LoadShaders();
	//シーンの初期化
	g_scene = new Scene;
	g_scene->SceneChange(g_scene->CHANGETITLE);
	//物理ワールドを初期化
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
	//フェードを初期化
	g_fade = new Fade;
	g_fade->Start();
	//シャドウマップを初期化
	g_shadowmap = new ShadowMap;
	g_shadowmap->Init();

}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	g_shadowmap->Update();
	
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		//シーンの描画開始。
		g_shadowmap->Draw();

		//あとで戻すためにフレームバッファのレンダリングターゲットとデプスステンシルバッファのバックアップを取る。
		LPDIRECT3DSURFACE9 frameBufferRT;
		LPDIRECT3DSURFACE9 frameBufferDS;
		g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
		g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);
		// レンダリングターゲットをフレームバッファから変更する。
		g_pd3dDevice->SetRenderTarget(
			0,
			g_renderTarget->GetRenderTarget()
		);
		//// デプスステンシルバッファも変更する。
		g_pd3dDevice->SetDepthStencilSurface(g_renderTarget->GetDepthStencilBuffer());
		// レンダリングターゲットをクリア。
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		//シーンの描画
		g_scene->Render();
		//フェードの描画
		g_fade->Draw();
		////シーンの描画が完了したのでレンダリングターゲットをフレームバッファに戻す。

		g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
		g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
		//参照カウンタが増えているので開放。
		frameBufferRT->Release();
		frameBufferDS->Release();
	}
	CopyMainRTToCurrentRT();

	//// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
*@brief	更新処理。
-----------------------------------------------------------------------------*/
void Update()
{
	g_physicsWorld->Update();
	g_scene->Update();
	g_fade->Update();
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	delete g_scene;
	delete g_fade;
	delete g_game;
	delete g_effectManager;
	delete g_shadowmap;
	delete g_physicsWorld;
	delete g_renderTarget;	
	delete m_primitive;		
	copyEffect->Release();
	g_pd3dDevice->Release();
	g_pD3D->Release();
}
//ステージ１完成
//バネカメラ、コースカメラ
//クローン？

