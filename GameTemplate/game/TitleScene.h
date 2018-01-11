#pragma once
#include "HUD.h"
#include "myEngine\HID\Pad.h"
//#include "BaseScene.h"
class TitleScene
{
public:
	//�R���X�g���N�^
	TitleScene();
	//�f�X�g���N�^
	~TitleScene();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Render();
	//�X�v���C�g�����֐�
	HRESULT CreateSprite();
private:
	//�X�e�[�g
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	//�I��
	enum Select{
		NO,
		START,
		BREAK,
	};
	Select				GAME = START;					//���
	EState				m_state = Run;					//�t�F�[�h
	LPD3DXSPRITE		m_sprite;						//�X�v���C�g
	HUD					m_title;						//�^�C�g���摜
	const D3DXVECTOR2	m_titlePos = { 595.0f,400.0f };	//�^�C�g���摜�̍��W
	Pad					m_pad;							//�p�b�h
	
};

