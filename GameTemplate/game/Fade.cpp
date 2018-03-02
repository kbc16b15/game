#include "stdafx.h"
#include "Fade.h"

Fade *Fade::m_fade = NULL;

Fade::Fade()
{
}
Fade::~Fade()
{
	m_fadeTex.Release();
}
void Fade::Init()
{
	m_isActive = false;
	m_fadeTex.Load("Assets/Sprite/TL.tga");
	m_fadeSprite.Init(&m_fadeTex);
	m_fadeSprite.SetSize(m_fadeScale);
	//m_fadetex.Update();
	//m_active = false;
	
}

void Fade::Update()
{
	//m_fadetex.Update();
	if (m_isExecute)
	{
		switch (m_state)
		{
		case eFadeOut:

			m_timer += m_frameDeltaTime;
			if (m_timer < FADE_TIME)
			{
				float t = m_timer / FADE_TIME;
				m_fadeSprite.SetAlpha(min(t, 1.0f));
				m_outtimer += m_frameDeltaTime;
			
			}
			else if (m_outtimer < 1)
			{
				m_fadeSprite.SetAlpha(1.0f);
				m_outtimer += m_frameDeltaTime;
			}
			else
			{
				m_fadeSprite.SetAlpha(1.0f);
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
				m_fadeSprite.SetAlpha(max(1.0f - t, 0.0f));
			}
			else
			{
				m_fadeSprite.SetAlpha(0.0f);
				//m_active = false;
				m_isActive = false;
				m_timer = FADE_TIME;
				m_isExecute = false;
				m_outtimer = 0;
			}
			break;

		}

		/*if (!m_fadetex.Getalfa() == 1.0f || !m_fadetex.Getalfa() == 0.0f)
		{
			m_fadetex.Initialize("Assets/Sprite/TL.tga", m_fadepos);
			CreateSprite();
		}*/
		
	}
}

void Fade::PostDraw()
{
		////g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		////g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		m_fadeSprite.Draw();
		////g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		//g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		////g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		
}
