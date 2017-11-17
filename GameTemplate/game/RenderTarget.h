#pragma once
class CRenderTarget
{
public:
	CRenderTarget();
	~CRenderTarget();
	void Release();
	void Create(
		int w,
		int h,
		int mipLevel,
		D3DFORMAT colorFormat,
		D3DFORMAT depthStencilFormat,
		D3DMULTISAMPLE_TYPE multiSampleType,
		int multiSampleQuality);
	//�����_�����O�^�[�Q�b�g���擾
	LPDIRECT3DSURFACE9 GetRenderTarget()
	{
		return m_surface;
	}
	//�f�v�X�X�e���V���o�b�t�@�̎擾
	LPDIRECT3DSURFACE9 GetDepthStencilBuffer()
	{
		return m_depthSurface;
	}
	//�e�N�X�`���擾
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_texture;
	}
private:
	LPDIRECT3DSURFACE9 m_surface;		//�T�[�t�F�C�X
	LPDIRECT3DTEXTURE9 m_texture;		//�������ݐ�̃e�N�X�`��
	LPDIRECT3DSURFACE9 m_depthSurface;	//�[�x�o�b�t�@�p�̃T�[�t�F�C�X
	//IDirect3DTexture9* m_tex;
};

