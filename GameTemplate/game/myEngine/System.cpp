#include "stdafx.h"
#include "System.h"

LPDIRECT3D9             g_pD3D = NULL;		
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;
EffectManager*			g_effectManager = NULL;

extern void Init();
extern void Render();
extern void Update();
extern void Terminate();
//-----------------------------------------------------------------------------
// DirectXを初期化。
//-----------------------------------------------------------------------------
void InitD3D(HWND hWnd)
{
	//D3Dオブジェクトを作成する。
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	// D3Dデバイスを作成するためのパラメータを設定する。
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//D3Dデバイスを作成する。
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice);

	g_effectManager = new EffectManager;

}
//-----------------------------------------------------------------------------
// メッセージプロシージャ。
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		if (g_pd3dDevice != NULL)
			g_pd3dDevice->Release();

		if (g_pD3D != NULL)
			g_pD3D->Release();
		Terminate();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//-----------------------------------------------------------------------------
// ウィンメイン。
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// ウィンドウクラスを登録。
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Game", NULL
	};
	RegisterClassEx(&wc);

	// ウィンドウを作成。
	HWND hWnd = CreateWindow("Game", "Game",
		WS_OVERLAPPEDWINDOW, 100, 100, FRAME_BUFFER_WIDTH + 100, FRAME_BUFFER_HEIGHT + 100,
		NULL, NULL, wc.hInstance, NULL);
	// Direct3Dを初期化。
	InitD3D(hWnd);

	// Show the window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//ここからゲーム関係の初期化。
	Init();
	
	// ゲームループ
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			Update();
			Render();
		}
	}
	UnregisterClass("Shader Tutorial", wc.hInstance);
	return 0;
}
