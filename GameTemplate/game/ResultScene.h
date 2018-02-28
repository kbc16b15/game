#pragma once
#include "IScene.h"
class ResultScene :public IScene
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
	void Draw();
	//�t�F�[�h
	void SceneFade();
	//�X�v���C�g�����֐�
	HRESULT CreateSprite();

private:
	//�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;
	LPD3DXSPRITE		m_sprite;						//�X�v���C�g
	HUD					m_resultHud;							//�^�C�g���摜
	const D3DXVECTOR2	m_resultHudPos = { 700.0f,300.0f };	//�^�C�g���摜�̍��W
};

