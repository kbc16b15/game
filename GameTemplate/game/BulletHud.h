#pragma once
#include "IGameObject.h"
#include "HUD.h"
class BulletHud :
	public IGameObject
{
public:

	~BulletHud();
	//初期化　座標の設定
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	//スプライト生成関数
	HRESULT CreateSprite();

	void SetBullet(bool isBullet)
	{
		m_isGun = isBullet;
	}

	void Setpos(D3DXVECTOR2 pos)
	{
		m_rockPos = pos;
	}
	//インスタンスの生成
	static void BulletHud::Create()
	{
		if (!m_bulletHud)
		{
			m_bulletHud = new BulletHud;
		}
	}

	//インスタンスの取得
	static BulletHud& GetInstance()
	{
		return *m_bulletHud;
	}

	//インスタンスの消去
	static  void BulletHud::Destroy()
	{
		delete m_bulletHud;
		m_bulletHud = nullptr;
	}
private:
	BulletHud();
	static BulletHud*	m_bulletHud;
	bool				m_isGun = false;			//照準の表示
	HUD					m_rock;
	LPD3DXSPRITE		m_sprite;					//スプライト
	D3DXVECTOR2			m_rockPos = { 700.0f, 250.0f };
};

