/*!
*@brief	�Q�[���e���v���[�g�B
*/
#include "stdafx.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/Light.h"
#include "Scene.h"
#include "Fade.h"
#include "ShadowMap.h"
#include "Primitive.h"
#include "RenderTarget.h"


LPD3DXEFFECT copyEffect;
LPD3DXEFFECT monochromeEffect;		//!<18-4 ���m�N���t�B���^�[��������V�F�[�_�[�B
Primitive*			m_primitive;				//�v���~�e�B�u

Game* g_game=nullptr;
Scene* g_scene=nullptr;
Fade* g_fade = nullptr;
ShadowMap* g_shadowmap= nullptr;
CRenderTarget*		g_renderTarget;				//�|�X�g�G�t�F�N�g�p�̃����_�����O�^�[�Q�b�g�H2


void InitMainRenderTarget()
{
	//18-2 ���C�������_�����O�^�[�Q�b�g���쐬����B
	g_renderTarget = new CRenderTarget;
	g_renderTarget->Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D16,				//�f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B��ʓI��16bit��24bit�t�H�[�}�b�g���g���邱�Ƃ������B�����24bit�t�H�[�}�b�g���g���B

		D3DMULTISAMPLE_NONE,
		0
	);
}

void DrawQuadPrimitive()
{
	// ���_�X�g���[��0�Ԃɔ|���̒��_�o�b�t�@��ݒ肷��B
	g_pd3dDevice->SetStreamSource(
		0,												//���_�X�g���[���̔ԍ��B
		m_primitive->GetVertexBuffer()->GetBody(),		//���_�o�b�t�@�B
		0,												//���_�o�b�t�@�̓ǂݍ��݂��J�n����I�t�Z�b�g�̃o�C�g���B
														//����͐擪����ǂݍ��ނ̂�0�ł����B
		m_primitive->GetVertexBuffer()->GetStride()		//���_����̃T�C�Y�B�P�ʂ̓o�C�g�B
	);
	// �C���f�b�N�X�o�b�t�@��ݒ�B
	g_pd3dDevice->SetIndices(m_primitive->GetIndexBuffer()->GetBody());
	// ���_��`��ݒ肷��B
	g_pd3dDevice->SetVertexDeclaration(m_primitive->GetVertexDecl());
	//�@�������������̂ŕ`��B
	g_pd3dDevice->DrawIndexedPrimitive(
		m_primitive->GetD3DPrimitiveType(),	//�v���~�e�B�u�̎�ނ��w�肷��B
		0,										//�x�[�X���_�C���f�b�N�X�B0�ł����B
		0,										//�ŏ��̒��_�C���f�b�N�X�B0�ł����B
		m_primitive->GetNumVertex(),			//���_�̐��B
		0,										//�J�n�C���f�b�N�X�B0�ł����B
		m_primitive->GetNumPolygon()			//�v���~�e�B�u�̐��B
	);
}

void InitQuadPrimitive()
{
	m_primitive = new Primitive;
	//���_�̍\���́B
	struct SVertex {
		float pos[4];	//���_���W�B
		float uv[2];	//UV���W�B
	};
	//���_�o�b�t�@�B
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};

	//���_���C�A�E�g�B���_�o�b�t�@�̍\�����ǂ̂悤�ɂȂ��Ă��邩��GPU�ɋ����邽�߂̂��́B
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//���_�X�g���[����0�Ԗڂ�0�o�C�g�ڂ���float�^��4���̃f�[�^�͍��W(D3DDECLUSAGE_POSITION)�ł��邱�Ƃ������Ă���B
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		//���_�X�g���[����0�Ԗڂ�16�o�C�g�ڂ���float�^��2���̃f�[�^��UV���W(D3DDECLUSAGE_TEXCOORD)�ł��邱�Ƃ������Ă���B
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};
	//�C���f�b�N�X�o�b�t�@�B
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	m_primitive->Create(
		Primitive::eTriangleStrip,	//����̓v���~�e�B�u�̎�ނ̓g���C�A���O���X�g���b�v�B
		4,							//���_�̐��B�l�p�`�̔|���Ńg���C�A���O���X�g���b�v�Ȃ̂łS�B
		sizeof(SVertex),			//���_�X�g���C�h�B��̒��_�̑傫���B�P�ʂ̓o�C�g�B
		scShapeVertex_PT_Element,	//���_���C�A�E�g�B
		vertexBuffer,				//���_�o�b�t�@�B
		4,							//�C���f�b�N�X�̐��B
		D3DFMT_INDEX16,				//�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g�B�����16bit�t�H�[�}�b�g���w�肷��B
									//�C���f�b�N�X�̐���65536�ȉ��̏ꍇ��16bit�ł������A����𒴂���ꍇ��D3DFMT_INDEX32���w�肷��B
		indexBuffer					//�C���f�b�N�X�o�b�t�@�B
	);
}

void LoadShaders()
{
	// �n���Y�I�� 4
	LPD3DXBUFFER compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/Copy.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif 
		NULL,
		&copyEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}

//	hr = D3DXCreateEffectFromFile(
//		g_pd3dDevice,
//		"Assets/Shader/MonochromeFilter.fx",
//		NULL,
//		NULL,
//#ifdef _DEBUG
//		D3DXSHADER_DEBUG,
//#else
//		D3DXSHADER_SKIPVALIDATION,
//#endif // _DEBUG
//		NULL,
//		&monochromeEffect,
//		&compileErrorBuffer
//	);
//
//	if (FAILED(hr))
//	{
//		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
//		std::abort();
//	}
}

void CopyMainRTToCurrentRT()
{
	// Z�e�X�g�Ŏ��s���Ă�������獢��̂ŁAZ�e�X�g�͖����ɂ��Ă����B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// ���u�����h������Ȃ��B
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);


	LPD3DXEFFECT shader = copyEffect;			//18-3 �R�s�[���s���V�F�[�_�[���g���ꍇ�͂�����B
												//LPD3DXEFFECT shader = monochromeEffect;		//18-4 ���m�N���t�B���^�[��������ꍇ�͂�������g�p����B
												//�V�F�[�_�[��ݒ�B
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//�V�[���e�N�X�`����ݒ肷��
	shader->SetTexture("g_tex", g_renderTarget->GetTexture());
	//�萔���W�X�^�ւ̕ύX���R�~�b�g����B
	shader->CommitChanges();
	DrawQuadPrimitive();
	shader->EndPass();
	shader->End();
	// �ύX���������_�����O�X�e�[�g�����ɖ߂��B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}
//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	InitMainRenderTarget();
	//18-3 �l�p�`�̔|���v���~�e�B�u���쐬�B
	InitQuadPrimitive();
	//18-3�A18-4 �V�F�[�_�[�����[�h�B
	LoadShaders();
	//�V�[���̏�����
	g_scene = new Scene;
	g_scene->SceneChange(g_scene->CHANGETITLE);
	//�������[���h��������
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();
	//�t�F�[�h��������
	g_fade = new Fade;
	g_fade->Start();
	//�V���h�E�}�b�v��������
	g_shadowmap = new ShadowMap;
	g_shadowmap->Init();

}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	g_shadowmap->Update();
	
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		//�V�[���̕`��J�n�B
		g_shadowmap->Draw();

		//���ƂŖ߂����߂Ƀt���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���o�b�t�@�̃o�b�N�A�b�v�����B
		LPDIRECT3DSURFACE9 frameBufferRT;
		LPDIRECT3DSURFACE9 frameBufferDS;
		g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
		g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);
		// �����_�����O�^�[�Q�b�g���t���[���o�b�t�@����ύX����B
		g_pd3dDevice->SetRenderTarget(
			0,
			g_renderTarget->GetRenderTarget()
		);
		//// �f�v�X�X�e���V���o�b�t�@���ύX����B
		g_pd3dDevice->SetDepthStencilSurface(g_renderTarget->GetDepthStencilBuffer());
		// �����_�����O�^�[�Q�b�g���N���A�B
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		//�V�[���̕`��
		g_scene->Render();
		//�t�F�[�h�̕`��
		g_fade->Draw();
		////�V�[���̕`�悪���������̂Ń����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B

		g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
		g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
		//�Q�ƃJ�E���^�������Ă���̂ŊJ���B
		frameBufferRT->Release();
		frameBufferDS->Release();
	}
	CopyMainRTToCurrentRT();

	//// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
*@brief	�X�V�����B
-----------------------------------------------------------------------------*/
void Update()
{
	g_physicsWorld->Update();
	g_scene->Update();
	g_fade->Update();
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	delete g_scene;
	delete g_fade;
	delete g_game;
	delete g_effectManager;
	delete g_shadowmap;
	delete g_physicsWorld;
	delete g_renderTarget;	
	delete m_primitive;		
	copyEffect->Release();
	g_pd3dDevice->Release();
	g_pD3D->Release();
}
//�X�e�[�W�P����
//�o�l�J�����A�R�[�X�J����
//�N���[���H

