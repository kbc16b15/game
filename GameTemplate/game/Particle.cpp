#include "stdafx.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "Primitive.h"
#include "VertexElement.h"

//struct SShapeVertex_PT {
//	float	pos[4];
//	float	uv[2];
//};
//static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
//	{0,0,D3DDECLTYPE_FLOAT4	,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
//	{0,16,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
//	D3DDECL_END()
//};

Particle::Particle()
{

	m_texture = nullptr;
	m_shaderEffect = nullptr;
}


Particle::~Particle()
{
	if (m_shaderEffect != nullptr)
	{
		m_shaderEffect->Release();
	}

	if (m_texture != nullptr) 
	{
		m_texture->Release();
	}
	m_primitive.Release();
}

void Particle::Init(const SParticleEmitParameter& param)
{

	srand((unsigned int)time(NULL));
	m_life = param.lifeTime;
	float halfW = param.w*0.5f;
	float halfH = param.h*0.5f;
	float addx = ((rand() % 255) - 128) / 128.0f;
	float addz = ((rand() % 255) - 128) / 128.0f;
	float addy = ((rand() % 255) - 128) / 128.0f;
	D3DXVECTOR4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	m_moveSpeed = param.initSpeed;
	m_position = param.position;//パーティクルの発生座標
	
	m_position.x += addx*param.Multipos;//パーティクルの発生座標に乱数を加えたい
	m_position.z += addz*param.Multipos;
	m_position.y += addy*param.Multipos;
	m_moveSpeed.x += addx*param.Multispeed.x;//初速度に乱数を加える
	m_moveSpeed.y += addy*param.Multispeed.y;
	m_moveSpeed.z += addz*param.Multispeed.z;

	SShapeVertex_PT vb[] = {
		{
			-halfW,halfH,0.0f,1.0f,
			uv.x,uv.y
		},
		{
			halfW,halfH,0.0f,1.0f,
			uv.z,uv.y
		},
		{
			-halfW,-halfH,0.0f,1.0f,
			uv.x,uv.w
		},
		{
			halfW,-halfH,0.0f,1.0f,
			uv.z,uv.w
		},
	};
	short index[]{
		0,1,2,3
	};
	m_primitive.Create(
		Primitive::eTriangleStrip,
		4,
		sizeof(SShapeVertex_PT),
		scShapeVertex_PT_Element,
		vb,
		4,
		D3DFMT_INDEX16,
		index
	);

	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice,param.texturePath,&m_texture);

	LPD3DXBUFFER compileErrorBuffer = NULL;
	hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"ColorTexPrim.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&m_shaderEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}

void Particle::Update() 
{
	if (m_isDead) { return; }
	//time--;
	float deltaTime = 1.0f / 60.0f;
	m_life -= deltaTime;
	//m_moveSpeed.y -= 0.1f;

	D3DXVECTOR3 add = m_moveSpeed*deltaTime;
	m_position += add;
	if (m_life < 0)
	{
		//delete this;
		m_isDead = true;
		//delete this;
	}
#if 0
	position.Add(addPos);
	CMatrix mTrans;
	mTrans.MakeTranslation(position);
	if (isBillboard) {
//ビルボード処理を行う
		const CMatrix& mCameraRot = camera->GetCameraRotation();
		CQuaternion qRot;
		qRot.SetRotation(CVecter3(mCameraRot.m[2][0], mCameraRot.m[2][1], mCamera.m[2][2]), rotateZ);
		CMatrix rot;
		rot.MakeRotationFromQuaternion(qRot);
		mWorld.Mul(mCameraRot, rot);
		mWorld.Mul(mWorld, mTrans);
	}
	else {
		mWorld = mTrans;
	}
	timer += deltaTime;
	switch (state) {
	case eStateRun:
		if (timer >= life) {
			if (isFade) {
				state = eStateFadeOut;
				timer = 0.0f;
			}
			else {
				stete = eStateDead;
			}
		}
		break;
	case eStateFadeOut: {
		float t = timer / fadeTIme;
		timer += deltaTime;
		alpha = initAlpha + (-initAlpha)*t;
		if (alpha <= 0.0f)
		{
			alpha = 0.0f;
			state = eStateDead;//死亡

		}

	}break;
	case eStateDead:
		GameObjectManager().DeleteGameObject(this);
		break;
	}
#endif
}

void Particle::HudDraw(/*const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix*/)
{
	if (m_isDead) { return; }
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	D3DXMATRIX m, mTrans;
	D3DXMatrixTranslation(&mTrans, m_position.x, m_position.y, m_position.z);
	//カメラ行列の逆行列
	D3DXMATRIX rot;
	D3DXMatrixInverse(&rot, NULL, &Camera::GetInstance().GetViewMatrix());
	//それをワールド行列に乗算する
	rot.m[3][0] = 0.0f;
	rot.m[3][1] = 0.0f;
	rot.m[3][2] = 0.0f;
	rot.m[3][3] = 1.0f;
	mTrans = rot*mTrans;
	m = mTrans*Camera::GetInstance().GetViewMatrix()*Camera::GetInstance().GetProjectionMatrix();

	/*g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);*/
	//αブレンディングを有効にする
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
	
	//shaderEffect->SetTechnique("ColorTexPrimTrans");
	m_shaderEffect->SetTechnique("ColorTexPrimAdd");

	m_shaderEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_shaderEffect->BeginPass(0);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	m_shaderEffect->SetValue("g_mWVP", &m, sizeof(m));
	m_shaderEffect->SetTexture("g_texture", m_texture);
	m_shaderEffect->CommitChanges();

	g_pd3dDevice->SetStreamSource(0, m_primitive.GetVertexBuffer()->GetBody(),0, m_primitive.GetVertexBuffer()->GetStride());
	g_pd3dDevice->SetIndices(m_primitive.GetIndexBuffer()->GetBody());
	g_pd3dDevice->SetVertexDeclaration(m_primitive.GetVertexDecl());
	g_pd3dDevice->DrawIndexedPrimitive(m_primitive.GetD3DPrimitiveType(), 0, 0, m_primitive.GetNumVertex(), 0, m_primitive.GetNumPolygon());
	m_shaderEffect->EndPass();
	m_shaderEffect->End();
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE,TRUE);

}
