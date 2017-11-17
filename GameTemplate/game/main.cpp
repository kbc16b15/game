/*!
*@brief	ゲームテンプレート。
*/
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Scene.h"
#include "Fade.h"
#include "ShadowMap.h"

Game* game=nullptr;
Scene* scene=nullptr;
Fade* g_fade = nullptr;
ShadowMap* g_shadowmap= nullptr;


//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	g_fade = new Fade;
	g_fade->Start();
	scene = new Scene;
	scene->SceneChange(scene->CHANGETITLE);
	g_shadowmap = new ShadowMap;
	g_shadowmap->Init();

}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	g_shadowmap->Update();
	//画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pd3dDevice->BeginScene();
		
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		g_shadowmap->Draw();

		scene->Render();
		g_fade->Draw();
	}

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
*@brief	更新処理。
-----------------------------------------------------------------------------*/
void Update()
{
	scene->Update();
	g_fade->Update();
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	delete scene;
	delete g_fade;
	delete game;
	delete g_effectManager;
}
//ステージ１完成
//慣性を付ける？
//バネカメラ、コースカメラ
//クローン？