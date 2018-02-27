/*!
*@brief	ゲームテンプレート。
*/
#include "stdafx.h"
#include "myEngine\Physics\Physics.h"
//#include "myEngine/Graphics/Camera.h"
#include "Fade.h"
#include "ShadowMap.h"
#include "Primitive.h"
#include "RenderTarget.h"
#include "TitleScene.h"
#include "SoundEngine.h"
#include "GameObjectManager.h"


//#include "game.h"
//#include <stdlib.h>
//#include <time.h>
//#include "TitleScene.h"
//#include "ResultScene.h"
//#include "ClearScene.h"
//#include "Fade.h"
//#include "Map.h"
//#include "ShadowMap.h"
//#include "bloom.h"
//#include "gameCamera.h"
//#include "Player.h"
//#include "PlayerHp.h"
//#include "EnemyManager.h"
//#include "BulletManager.h"
//#include "GameObjectManager.h"
//#include "SceneChange.h"

LPD3DXEFFECT	copyEffect;
//LPD3DXEFFECT	monochromeEffect;			//!<18-4 モノクロフィルターをかけるシェーダー。

void InitMainRenderTarget()
{
	//メインレンダリングターゲットを作成する。
	RenderTarget::MainRenderTargetCreate();
	RenderTarget::MainRenderTargetGetInstance().Create(
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
		Primitive::GetMainPrimitive().GetVertexBuffer()->GetBody(),		//頂点バッファ。
		0,												//頂点バッファの読み込みを開始するオフセットのバイト数。
														//今回は先頭から読み込むので0でいい。
		Primitive::GetMainPrimitive().GetVertexBuffer()->GetStride()		//頂点一つ分のサイズ。単位はバイト。
	);
	// インデックスバッファを設定。
	g_pd3dDevice->SetIndices(Primitive::GetMainPrimitive().GetIndexBuffer()->GetBody());
	// 頂点定義を設定する。
	g_pd3dDevice->SetVertexDeclaration(Primitive::GetMainPrimitive().GetVertexDecl());
	//　準備が整ったので描画。
	g_pd3dDevice->DrawIndexedPrimitive(
		Primitive::GetMainPrimitive().GetD3DPrimitiveType(),	//プリミティブの種類を指定する。
		0,										//ベース頂点インデックス。0でいい。
		0,										//最小の頂点インデックス。0でいい。
		Primitive::GetMainPrimitive().GetNumVertex(),			//頂点の数。
		0,										//開始インデックス。0でいい。
		Primitive::GetMainPrimitive().GetNumPolygon()			//プリミティブの数。
	);
}

void InitQuadPrimitive()
{
	Primitive::CreateMainPrimitive();
	//m_primitive = new Primitive;
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
	Primitive::GetMainPrimitive().Create(
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
	shader->SetTexture("g_tex", RenderTarget::MainRenderTargetGetInstance().GetTexture()/*g_renderTarget->GetTexture()*/);
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



	CubeCollision::Create();
	InitMainRenderTarget();
	//18-3 四角形の板ポリプリミティブを作成。
	InitQuadPrimitive();
	//18-3、18-4 シェーダーをロード。
	LoadShaders();
	GameObjectManager::Create();
	//物理ワールドを初期化
	PhysicsWorld::Create();
	PhysicsWorld::GetInstance().Init();
	//シーンの初期化
	SoundEngine::Create();
	SoundEngine::GetInstance().Init();
	TitleScene::Create();
	Pad::Create();
	//フェード
	Fade::Create();

	//シャドウマップ
	ShadowMap::Create();
	ShadowMap::GetInstance().Init();

	Fade::GetInstance().Init();
	TitleScene::GetInstance().SetStart(true);
	TitleScene::GetInstance().Init();
	GameObjectManager::GetGameObjectManager().AddGameObject(&Fade::GetInstance());
	GameObjectManager::GetGameObjectManager().AddGameObject(&TitleScene::GetInstance());


	//SceneChange::Create();
	//Player::Create();
	//PlayerHp::Create();
	//BulletManager::Create();
	//EnemyManager::Create();
	//Map::Create();
	//gameCamera::Create();
	//Bloom::Create();

	////プレイヤー初期化
	//Player::GetInstance().Init();
	//PlayerHp::GetInstance().Init();
	////マップを初期化
	//Map::GetInstance().SetStage(SceneChange::GetInstance().GetMapNo());
	//Map::GetInstance().Init();

	////カメラ初期化。
	//gameCamera::GetInstance().Init();
}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	ShadowMap::GetInstance().Update();
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		//シーンの描画開始。
		ShadowMap::GetInstance().Draw();
		//g_shadowMap->Draw();
		//あとで戻すためにフレームバッファのレンダリングターゲットとデプスステンシルバッファのバックアップを取る。
		LPDIRECT3DSURFACE9 frameBufferRT;
		LPDIRECT3DSURFACE9 frameBufferDS;
		g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
		g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);
		// レンダリングターゲットをフレームバッファから変更する。
		g_pd3dDevice->SetRenderTarget(
			0,
			RenderTarget::MainRenderTargetGetInstance().GetRenderTarget()
			//g_renderTarget->GetRenderTarget()
		);
		//// デプスステンシルバッファも変更する。
		g_pd3dDevice->SetDepthStencilSurface(RenderTarget::MainRenderTargetGetInstance().GetDepthStencilBuffer());
		// レンダリングターゲットをクリア。
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		//シーンの描画
		GameObjectManager::GetGameObjectManager().Draw();

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
	// バックバッファとフロントバッファを入れ替える
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
*@brief	更新処理。
-----------------------------------------------------------------------------*/
void Update()
{

	SoundEngine::GetInstance().Update();
	Pad::GetInstance().Update();
	PhysicsWorld::GetInstance().Update();
	GameObjectManager::GetGameObjectManager().Update();

}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	PhysicsWorld::GetInstance().Destroy();
	//delete m_primitive;
	Primitive::GetMainPrimitive().Release();
	Primitive::GetMainPrimitive().DestroyMainPrimitive();
	RenderTarget::MainRenderTargetGetInstance().Destroy();
	ShadowMap::GetInstance().Destroy();
	Pad::GetInstance().Destroy();
	GameObjectManager::GetGameObjectManager().DeleteGameObject(&Fade::GetInstance());
	Fade::GetInstance().Destroy();
	GameObjectManager::GetGameObjectManager().Destroy();
	SoundEngine::GetInstance().Release();
	copyEffect->Release();
	g_pd3dDevice->Release();
	g_pD3D->Release();
	g_effectManager->Release();
	//delete g_effectManager;

}
//クローン