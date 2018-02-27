#include "stdafx.h"
#include "BulletHud.h"
#include "gameCamera.h"
#include "Player.h"
#include "BulletManager.h"

BulletHud *BulletHud::m_bulletHud = NULL;

BulletHud::BulletHud()
{
}

BulletHud::~BulletHud()
{
}

void BulletHud::Init()
{
	m_rock.Setalfa(0.5f);
	m_rock.Initialize("Assets/Sprite/Rock.jpg", m_rockPos);
	CreateSprite();
}

void BulletHud::Update()
{

	//m_rock.Initialize("Assets/Sprite/Rock.jpg", m_rockPos);
	//const float playerBulletSpeed = 0.3f;
	//if (GetAsyncKeyState('Z') || Pad::GetInstance().IsTrigger(Pad::GetInstance().enButtonRB1) && m_isGun)
	//{
	//	D3DXVECTOR3 Ppos = Player::GetInstance().Getpos();
	//	D3DXVECTOR3 Cpos = SpringCamera::GetInstance().GetTarTarget();
	//	Bullet* bullet = BulletManager::GetInstance().CreateBullet(bullet->PLAYER);
	//	bullet->Start({ Cpos.x ,Cpos.y ,Cpos.z }, playerBulletSpeed, bullet->PLAYER);
	//}
	//m_rock.Update();
}

void BulletHud::Draw()
{
	if (m_isGun)
	{
		m_rock.Draw(m_sprite);
	}

}

HRESULT BulletHud::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_sprite)))
	{
		MessageBox(0, TEXT("ÉXÉvÉâÉCÉgçÏê¨é∏îs"), NULL, MB_OK);
		return E_FAIL;//é∏îsï‘ãp
	}
	return S_OK;
}