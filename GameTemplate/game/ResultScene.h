#pragma once
#include "HUD.h"
#include "myEngine\HID\Pad.h"
//#include "BaseScene.h"
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
	//�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	//�I��
	enum Select {
		NO,
		START,
		BREAK,
	};
	Select				GAME = START;
	EState				m_state = Run;
	LPD3DXSPRITE		m_sprite;						//�X�v���C�g
	HUD					m_end;							//�^�C�g���摜
	const D3DXVECTOR2	m_endPos = { 700.0f,300.0f };	//�^�C�g���摜�̍��W
	Pad					m_pad;							//�p�b�h
};

