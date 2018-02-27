#include "stdafx.h"
#include "bloom.h"

Bloom *Bloom::m_bloom = NULL;

void Bloom::UpdateWeight(float dispersion)
{
	float total = 0;
	for (int i = 0;i < NUM_WEIGHT;i++)
	{
		weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
		total += 2.0f*weights[i];
	}
	//規格化
	for (int i = 0;i < NUM_WEIGHT;i++)
	{
		weights[i] /= total;
	}
}


Bloom::Bloom()
{

	//ブルームのシェーダーをロード
	effect = g_effectManager->LoadEffect("Assets/Shader/bloom.fx");

	luminanceRenderTarget.Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
	);

	int w = FRAME_BUFFER_WIDTH;
	int h = FRAME_BUFFER_HEIGHT;
	for (int i = 0;i < MGF_DOWN_SAMPLE_COUNT;i++)
	{
		w /= 2;
		//横ブラー
		downSamplingRenderTarget[i][0].Create(
			w,
			h,
			1,
			D3DFMT_A8R8G8B8,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0
		);
		h /= 2;
		//縦ブラー
		downSamplingRenderTarget[i][1].Create(
			w ,
			h ,
			1,
			D3DFMT_A8R8G8B8,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0
		);
	}
}


Bloom::~Bloom()
{
	luminanceRenderTarget.Release();
	for (int i = 0;i < MGF_DOWN_SAMPLE_COUNT;i++)
	{
		//横ブラー
		downSamplingRenderTarget[i][0].Release();
		//縦ブラー
		downSamplingRenderTarget[i][1].Release();
	}
	//effect->Release();
	
}

void Bloom::Update() 
{


}
void Bloom::Draw()
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	{
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		g_pd3dDevice->SetRenderTarget(0, luminanceRenderTarget.GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(luminanceRenderTarget.GetDepthStencilBuffer());
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		effect->SetTechnique("SamplingLuminance");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);

		effect->SetTexture("g_scene", RenderTarget::MainRenderTargetGetInstance().GetTexture());

		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

		// 変更したレンダリングステートを元に戻す。
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	UpdateWeight(25.0f);
#if 1
	//Xブラー
	int luminanceTexW = luminanceRenderTarget.GetWidth();
	int luminanceTexH = luminanceRenderTarget.GetHeight();
	LPDIRECT3DTEXTURE9 blurTexture = luminanceRenderTarget.GetTexture();
	for (int i = 0; i < MGF_DOWN_SAMPLE_COUNT; i++) {

		g_pd3dDevice->SetRenderTarget(0,downSamplingRenderTarget[i][0].GetRenderTarget());

		effect->SetTechnique("XBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		float size[2];
		size[0] = (float)luminanceTexW;
		size[1] = (float)luminanceTexH;
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		/* = {
			(float)(luminanceRenderTarget.GetWidth()),
			(float)(luminanceRenderTarget.GetHeight())
		};*/
		float offset[2];
		offset[0] = 8.0f / size[0];
		offset[1] = 0.0f;
		effect->SetValue("g_offset", offset, sizeof(offset));

		/*float offset[] = {
			16.0f / (float)(luminanceRenderTarget.GetWidth()),
			0.0f
		};*/
		//effect->SetValue("g_offset", offset, sizeof(size));

		float renderTargetSize[2];
		renderTargetSize[0] = (float)downSamplingRenderTarget[i][0].GetWidth();
		renderTargetSize[1] = (float)downSamplingRenderTarget[i][0].GetHeight();
		effect->SetValue("g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));
		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", blurTexture);
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();


		//Yブラー
		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[i][1].GetRenderTarget());

		effect->SetTechnique("YBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);

		blurTexture = downSamplingRenderTarget[i][0].GetTexture();

		size[0] = (float)downSamplingRenderTarget[i][0].GetWidth();
		size[1] = (float)downSamplingRenderTarget[i][0].GetHeight();
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//オフセットを転送。
		offset[0] = 0.0f;
		offset[1] = 8.0f / size[1];
		effect->SetValue("g_offset", offset, sizeof(offset));

		/* 
		offset[] = {
			0.0f,
			16.0f / (float)(downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][0].GetHeight())
		};*/

		//レンダリングターゲットのサイズを転送。
		renderTargetSize[0] = (float)downSamplingRenderTarget[i][1].GetWidth();
		renderTargetSize[1] = (float)downSamplingRenderTarget[i][1].GetHeight();
		effect->SetValue("g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));

		//effect->SetValue("g_luminanceTexSize", size, sizeof(size));
		//effect->SetValue("g_offset", offset, sizeof(size));
		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", blurTexture);
		effect->SetFloat("g_mulYBlurOutputColor", ((float)(MGF_DOWN_SAMPLE_COUNT - i)) / MGF_DOWN_SAMPLE_COUNT);
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();



		luminanceTexW = downSamplingRenderTarget[i][1].GetWidth();
		luminanceTexH = downSamplingRenderTarget[i][1].GetHeight();
		
	}
	//最終合成

	/*offset[] = {
	0.5f / downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][1].GetWidth(),
	0.5f / downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][1].GetHeight()
	};*/
	g_pd3dDevice->SetRenderTarget(0, RenderTarget::MainRenderTargetGetInstance().GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(RenderTarget::MainRenderTargetGetInstance().GetDepthStencilBuffer());

	//加算合成
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	effect->SetTechnique("Final");
	effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	effect->BeginPass(0);
	effect->SetTexture("g_combineTex00", downSamplingRenderTarget[0][1].GetTexture());
	effect->SetTexture("g_combineTex01", downSamplingRenderTarget[1][1].GetTexture());
	effect->SetTexture("g_combineTex02", downSamplingRenderTarget[2][1].GetTexture());
	effect->SetTexture("g_combineTex03", downSamplingRenderTarget[3][1].GetTexture());
	effect->SetTexture("g_combineTex04", downSamplingRenderTarget[4][1].GetTexture());
	effect->CommitChanges();
	DrawQuadPrimitive();

	effect->EndPass();
	effect->End();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
#else
g_pd3dDevice->SetRenderTarget(0, RenderTarget::MainRenderTargetGetInstance().GetRenderTarget());
g_pd3dDevice->SetDepthStencilSurface(RenderTarget::MainRenderTargetGetInstance().GetDepthStencilBuffer());

#endif
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}