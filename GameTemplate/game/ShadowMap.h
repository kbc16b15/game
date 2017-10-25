#pragma once
#include "RenderTarget.h"
class ShadowMap
{
public:
	//�R���X�g���N�^
	ShadowMap();
	//�f�X�g���N�^�B
	~ShadowMap();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�e�N�X�`���̎擾
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return renderTarget.GetTexture();
	}
	//���C�g�r���[�̎��_�̐ݒ�
	void SetviewPosition(const D3DXVECTOR3& viewPos)
	{
		viewPosition = viewPos;
	}
	//���C�g�r���[�̒����_�̐ݒ�
	void SetviewTarget(const D3DXVECTOR3& vTarget)
	{
		viewTarget = vTarget;
	}
	//���C�g�v���W�F�N�V�����s��̎擾
	const D3DXMATRIX& GetlightProjectionMatrix()
	{
		return lightProjectionMatrix;
	}
	//���C�g�r���[�s��̎擾
	const D3DXMATRIX& GetlightViewMatrix()
	{
		return lightViewMatrix;
	}

private:
	CRenderTarget	renderTarget;//�V���h�E�}�b�v���������ރ����_�����O�^�[�Q�b�g
	D3DXMATRIX	lightViewMatrix;//���C�g�r���[�}�g���N�X�B�J������Ԃɕϊ�
	D3DXMATRIX	lightProjectionMatrix;//���C�g�v���W�F�N�V�����}�g���N�X�B�X�N���[����Ԃɕϊ�
	D3DXVECTOR3	viewPosition = {0.0f,0.0f,0.0f};//���C�g�r���[�̎��_�B
	D3DXVECTOR3 viewTarget = { 0.0f,0.0f,0.0f };//���C�g�r���[�̒����_�B
};

