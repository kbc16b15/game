#pragma once
//#include "IGameObject.h"
#include "IScene.h"
#include "HUD.h"
class ClearScene :public IScene
{
public:
	//�R���X�g���N�^
	ClearScene();
	//�f�X�g���N�^
	~ClearScene();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void /*PrePost*/Draw();
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
	EState				m_state = Run;
	LPD3DXSPRITE		m_sprite;						//�X�v���C�g
	HUD					m_clearHud;							//�^�C�g���摜
	const D3DXVECTOR2	m_clearHudPos = { 620.0f,400.0f };	//�^�C�g���摜�̍��W
};

