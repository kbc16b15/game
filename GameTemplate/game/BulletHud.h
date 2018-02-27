#pragma once
#include "IGameObject.h"
#include "HUD.h"
class BulletHud :
	public IGameObject
{
public:

	~BulletHud();
	//�������@���W�̐ݒ�
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�X�v���C�g�����֐�
	HRESULT CreateSprite();

	void SetBullet(bool isBullet)
	{
		m_isGun = isBullet;
	}

	void Setpos(D3DXVECTOR2 pos)
	{
		m_rockPos = pos;
	}
	//�C���X�^���X�̐���
	static void BulletHud::Create()
	{
		if (!m_bulletHud)
		{
			m_bulletHud = new BulletHud;
		}
	}

	//�C���X�^���X�̎擾
	static BulletHud& GetInstance()
	{
		return *m_bulletHud;
	}

	//�C���X�^���X�̏���
	static  void BulletHud::Destroy()
	{
		delete m_bulletHud;
		m_bulletHud = nullptr;
	}
private:
	BulletHud();
	static BulletHud*	m_bulletHud;
	bool				m_isGun = false;			//�Ə��̕\��
	HUD					m_rock;
	LPD3DXSPRITE		m_sprite;					//�X�v���C�g
	D3DXVECTOR2			m_rockPos = { 700.0f, 250.0f };
};

