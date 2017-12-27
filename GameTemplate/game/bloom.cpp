#include "stdafx.h"
#include "bloom.h"


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
	//横ブラー
	downSamplingRenderTarget[0].Create(
		FRAME_BUFFER_WIDTH / 2,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
	);
	//縦ブラー
	downSamplingRenderTarget[1].Create(
		FRAME_BUFFER_WIDTH / 2,
		FRAME_BUFFER_HEIGHT / 2,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
	);
}


Bloom::~Bloom()
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

		effect->SetTexture("g_scene", g_renderTarget->GetTexture());

		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

		// 変更したレンダリングステートを元に戻す。
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	UpdateWeight(25.0f);
	//Xブラー
	{
		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[0].GetRenderTarget());

		effect->SetTechnique("XBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		float size[2] = {
			(float)(luminanceRenderTarget.GetWidth()),
			(float)(luminanceRenderTarget.GetHeight())
		};
		float offset[] = {
			16.0f / (float)(luminanceRenderTarget.GetWidth()),
			0.0f
		};
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));
		effect->SetValue("g_offset", offset, sizeof(size));
		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", luminanceRenderTarget.GetTexture());
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
	}

	//Yブラー
	{
		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[1].GetRenderTarget());

		effect->SetTechnique("YBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		float size[2] = {
			(float)(downSamplingRenderTarget[0].GetWidth()),
			(float)(downSamplingRenderTarget[0].GetHeight())
		};
		float offset[] = {
			0.0f,
			16.0f / (float)(downSamplingRenderTarget[0].GetHeight())
		};
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));
		effect->SetValue("g_offset", offset, sizeof(size));
		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", downSamplingRenderTarget[0].GetTexture());
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
	}


	{
		//最終合成
		float offset[] = {
			0.5f / downSamplingRenderTarget[1].GetWidth(),
			0.5f / downSamplingRenderTarget[1].GetHeight()
		};
		g_pd3dDevice->SetRenderTarget(0, g_renderTarget->GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(g_renderTarget->GetDepthStencilBuffer());

		//加算合成
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		effect->SetTechnique("Final");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		effect->SetTexture("g_blur", downSamplingRenderTarget[1].GetTexture());
		effect->SetValue("g_offset", offset, sizeof(offset));
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}