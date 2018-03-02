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
	//HRESULT CreateSprite();

private:
	//�t�F�[�h
	enum EState {
		WaitFadeIn,
		Run,
		WaitFadeOut
	};
	EState				m_state = WaitFadeIn;
	Sprite				m_resultSprite;						//�X�v���C�g�B
	Texture				m_resultTexture;						//�w�i�̃e�N�X�`���B
	const D3DXVECTOR2	m_resultPos = { 0.0f,100.0f };	//�摜�̍��W
	const D3DXVECTOR2	m_resultScale = { 1300.0f,1200.0f };//�g��
};

