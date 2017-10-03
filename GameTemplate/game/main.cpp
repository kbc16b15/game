/*!
*@brief	ゲームテンプレート。
*/
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Scene.h"
#include "Fade.h"
Game* game=nullptr;
Scene* scene=nullptr;
Fade* g_fade = nullptr;
//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	g_fade = new Fade;
	g_fade->Start();
	scene = new Scene;
	scene->Init();
}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	//画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();
	scene->Render();
	g_fade->Draw();


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

//サウンドを入れる
//α作成
//自分の考えたステージ1番目を作成
//カメラの当たりを作る
//プレイヤーが壁の奥にいても透けて見えるようにする
