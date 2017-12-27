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
		return m_renderTarget.GetTexture();
	}
	//���C�g�r���[�̎��_�̐ݒ�
	void SetviewPosition(D3DXVECTOR3 viewPos)
	{
		m_viewPosition = viewPos;
	}
	//���C�g�r���[�̒����_�̐ݒ�
	void SetviewTarget(D3DXVECTOR3 vTarget)
	{
		m_viewTarget = vTarget;
	}
	//���C�g�v���W�F�N�V�����s��̎擾
	D3DXMATRIX GetlightProjectionMatrix()
	{
		return m_lightProjectionMatrix;
	}
	//���C�g�r���[�s��̎擾
	D3DXMATRIX GetlightViewMatrix()
	{
		return m_lightViewMatrix;
	}


private:
	CRenderTarget	m_renderTarget;//�V���h�E�}�b�v���������ރ����_�����O�^�[�Q�b�g
	D3DXMATRIX	m_lightViewMatrix;//���C�g�r���[�}�g���N�X�B�J������Ԃɕϊ�
	D3DXMATRIX	m_lightProjectionMatrix;//���C�g�v���W�F�N�V�����}�g���N�X�B�X�N���[����Ԃɕϊ�
	D3DXVECTOR3	m_viewPosition;//���C�g�r���[�̎��_�B
	D3DXVECTOR3 m_viewTarget;//���C�g�r���[�̒����_�B
	//SkinModel	skinModel;
};

extern ShadowMap* g_shadowmap;

