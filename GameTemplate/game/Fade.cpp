#include "stdafx.h"
#include "Fade.h"

Fade *Fade::m_fade = NULL;

Fade::Fade()
{

}


Fade::~Fade()
{
}

void Fade::Init()
{
	m_fadetex.Initialize("Assets/Sprite/TL.tga", m_fadepos);
	CreateSprite();
	m_active = false;
}

void Fade::Update()
{
	if (m_active)
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
					m_outtimer += m_frameDeltaTime;
			
				}
				else if (m_outtimer < 1)
				{
					m_fadetex.Setalfa(1.0f);
					m_outtimer += m_frameDeltaTime;
				}
				else
				{
					m_fadetex.Setalfa(1.0f);
					m_isExecute = false;
					m_outtimer = 0;
				}
				break;
			case eFadeIn:
				/*m_outtimer += m_frameDeltaTime;
				if (m_outtimer < 0.5) { return; }*/

				m_timer += m_frameDeltaTime;
				if (m_timer < FADE_TIME)
				{
					float t = m_timer / FADE_TIME;
					m_fadetex.Setalfa(max(1.0f - t, 0.0f));
				}
				else
				{
					m_fadetex.Setalfa(0.0f);
					m_active = false;
					m_timer = FADE_TIME;
					m_isExecute = false;
					m_outtimer = 0;
				}
				break;

			}

			if (!m_fadetex.Getalfa() == 1.0f || !m_fadetex.Getalfa() == 0.0f)
			{
				m_fadetex.Initialize("Assets/Sprite/TL.tga", m_fadepos);
				CreateSprite();
			}
			
		}
	}
}

void Fade::PostDraw()
{
	if (m_active)
	{
		////g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		////g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		m_fadetex.Draw(m_sprite);
		////g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		////g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	}

		
}

HRESULT Fade::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("ÉXÉvÉâÉCÉgçÏê¨é∏îs"), NULL, MB_OK);
		return E_FAIL;//é∏îsï‘ãp
	}
	return S_OK;
}
