#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
}


Fade::~Fade()
{
}

void Fade::Start()
{
	m_fadetex.Initialize("Assets/Sprite/LL.png",fadepos);
	CreateSprite();
	Active = false;
}

void Fade::Update()
{
	if (Active)
	{
		m_fadetex.Update();
		if (m_isExecute)
		{
			switch (m_state)
			{
			case eFadeOut:

				m_timer += m_frameDeltaTime;
				if (m_timer < FADE_TIME)
				{
					float t = m_timer / FADE_TIME;
					m_fadetex.Setalfa(min(t, 1.0f));
					Outtimer += m_frameDeltaTime;
			
				}
				else if (Outtimer < 0.8)
				{
					m_fadetex.Setalfa(1.0f);
					Outtimer += m_frameDeltaTime;
				}
				else
				{
					m_fadetex.Setalfa(1.0f);
					m_isExecute = false;
					Outtimer = 0;
				}
				break;
			case eFadeIn:
				Outtimer += m_frameDeltaTime;
				if (Outtimer < 1.5) { return; }

				m_timer += m_frameDeltaTime;
				if (m_timer < FADE_TIME)
				{
					float t = m_timer / FADE_TIME;
					m_fadetex.Setalfa(max(1.0f - t, 0.0f));
				}
				else
				{
					m_fadetex.Setalfa(0.0f);
					Active = false;
					m_timer = FADE_TIME;
					m_isExecute = false;
					Outtimer = 0;
				}
				break;

			}

			if (!m_fadetex.Getalfa() == 1.0f || !m_fadetex.Getalfa() == 0.0f)
			{
				m_fadetex.Initialize("Assets/Sprite/LL.png", fadepos);
				//CreateSprite();
			}
		}
	}
}

void Fade::Draw()
{
	if (Active)
	{
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		m_fadetex.Draw(m_Sprite);
		//g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, FALSE);*/
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	}

		
}

HRESULT Fade::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_Sprite)))
	{
		MessageBox(0, TEXT("ÉXÉvÉâÉCÉgçÏê¨é∏îs"), NULL, MB_OK);
		return E_FAIL;//é∏îsï‘ãp
	}
	return S_OK;
}
