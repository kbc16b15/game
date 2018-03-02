#pragma once
//#include "IGameObject.h"
#include "IScene.h"
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
	
private:
	//�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = Run;
	Sprite				m_clearSprite;						//�X�v���C�g�B
	Texture				m_clearTexture;						//�w�i�̃e�N�X�`���B
	const D3DXVECTOR2	m_clearPos = { 0.0f,0.0f };		//�摜�̍��W
	const D3DXVECTOR2	m_clearScale = { 1300.0f,900.0f };//�g��
};

