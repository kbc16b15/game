#pragma once
#include "HUD.h"
#include "myEngine\HID\Pad.h"
class ResultScene
{
public:
	//�R���X�g���N�^
	ResultScene();
	//�f�X�g���N�^
	~ResultScene();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Render();
	//�X�v���C�g�����֐�
	HRESULT CreateSprite();
private:

	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};

	enum Select {
		NO,
		START,
		BREAK,
	};
	Select GAME = START;
	EState      m_state = Run;

	LPD3DXSPRITE		m_Sprite;						//�X�v���C�g
	HUD					m_End;						//�^�C�g���摜
	const D3DXVECTOR2	endpos = { 700.0f,300.0f };	//�^�C�g���摜�̍��W
	Pad					pad;								//�p�b�h
};

