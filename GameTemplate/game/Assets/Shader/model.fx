/*!
 * @brief	�X�L�����f���V�F�[�_�[�B(4�{�[���X�L�j���O)
 */

#include "LightingFunction.h"

//�X�L���s��B
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//���̐��B

float4x4	g_viewMatrix;			//!�r���[
float4x4	g_projectionMatrix;		//!�v���W�F�N�V�����s��
float4x4	g_worldMatrix;			//!<���[���h�s��B
float4x4	g_rotationMatrix;		//!<��]�s��B
float4x4	g_viewMatrixRotInv;		//!<�J�����̉�]�s��̋t�s��B

float4x4 g_viewlightMatrix;
float4x4 g_projlightMatrix;

bool g_Reciver;
bool g_isSpecularlight;
float g_Scroll;
int g_MoveDir;

float3 Eye;				//�J�������W
bool g_isHasNormalMap;			//�@���}�b�v�ێ����Ă���H
int g_isHasSpecularMap;		//�X�y�L�����}�b�v�ێ��H
texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

texture g_shadowMapTexture;		//�V���h�E�}�b�v�e�N�X�`���B
sampler g_shadowMapTextureSampler = 
sampler_state
{
	Texture = <g_shadowMapTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Clamp;
	AddressV = Clamp;
};

//�@���}�b�v
texture g_normalTexture;		//�@���}�b�v�B
sampler g_normalMapSampler = 
sampler_state
{
	Texture = <g_normalTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

//�X�y�L�����}�b�v
texture g_specularTexture;
sampler g_specularMapSampler=
sampler_state
{
	Texture=<g_specularTexture>;
	MipFilter=LINEAR;
	MinFilter=LINEAR;
	MagFilter=LINEAR;
	AddressU=Wrap;
	AddressV=Wrap;
};

//�L���[�u�}�b�v
texture g_cubeTex;
sampler g_cubeTexSampler=
sampler_state{
 	Texture=<g_cubeTex>;
 	MipFilter=LINEAR;
	MinFilter=LINEAR;
 	MagFilter=LINEAR;
	AddressU=Wrap;
	AddressV=Wrap;
};
/*!
 * @brief	���͒��_
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
    float3	Tangent			: TANGENT;		//�ڃx�N�g��
    float3  Tex0            : TEXCOORD0;
    //float4  color		:COLOR0;
   //float2 uv			:TEXCOORD4;
};

/*!
 * @brief	�o�͒��_�B
 */
struct VS_OUTPUT
{

	float4  Pos     		: POSITION;
    float3  Normal			: NORMAL;
    float2  Tex0   			: TEXCOORD0;
    float3	Tangent			: TEXCOORD1;	//�ڃx�N�g��
    float3 world			: TEXCOORD2;	//���[���h�̕ϊ����W
    float4 lightViewPos 		: TEXCOORD3;
 
    //float4  color		:COLOR0;
    float3 worldPos			:TEXCOORD4;

};
/*!
 *@brief	���[���h���W�ƃ��[���h�@�����X�L���s�񂩂�v�Z����B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//�u�����h���[�g�B
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
    int   IndexArray[4]        = (int[4])IndexVector;
    float LastWeight = 0.0f;
    for (int iBone = 0; iBone < g_numBone-1; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        
        Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Tangent += mul(In.Tangent, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    }
    LastWeight = 1.0f - LastWeight; 
    
	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Tangent += (mul(In.Tangent, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
}
/*!
 *@brief	���[���h���W�ƃ��[���h�@�����v�Z�B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	Normal = mul(In.Normal, g_rotationMatrix );
	Tangent = mul(In.Tangent, g_rotationMatrix );
}
/*!
 *@brief	���_�V�F�[�_�[�B
 *@param[in]	In			���͒��_�B
 *@param[in]	hasSkin		�X�L������H
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	
	if(hasSkin){
		//�X�L������B
	    CalcWorldPosAndNormalFromSkinMatrix( In, Pos, Normal, Tangent );

	}else{
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal( In, Pos, Normal, Tangent );
	}
		o.worldPos=Pos.xyz;
		//float4 worldPos=mul( Pos, g_worldMatrix );
		o.world=Pos;
        o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
        
        o.Normal = normalize(Normal);
        o.Tangent = normalize(Tangent);
        o.Tex0 = In.Tex0;

       if(g_Reciver==1)
       {
	  	o.lightViewPos=mul(float4(o.world, 1.0f),g_viewlightMatrix);
	  	//o.lightViewPos=mul(worldPos,g_viewlightMatrix);
	   	o.lightViewPos=mul(o.lightViewPos,g_projlightMatrix);
       }
    return o;
}


/*!
 * @brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float4 color;
	if(!g_MoveDir)
	{
		color=tex2D(g_diffuseTextureSampler, In.Tex0);
	}else
	{
		color = tex2D(g_diffuseTextureSampler, In.Tex0+float2(0.0f,g_Scroll));
	}
	float3 normal = In.Normal;
	

	if(g_isHasNormalMap){
		//�@���}�b�v������B
		float3 tangent = normalize(In.Tangent);
		float3 binSpaceNormal = tex2D( g_normalMapSampler, In.Tex0);
		float4x4 tangentSpaceMatrix;
		//�@���ƃ^���W�F���g����]�@�������߂�
		float3 biNormal = normalize( cross( tangent, normal) );
		//�^���W�F���g�X�y�[�X���烏�[���h�X�y�[�X�ɕϊ�����s������߂�B
		tangentSpaceMatrix[0] = float4( tangent, 0.0f);
		tangentSpaceMatrix[1] = float4( biNormal, 0.0f);
		tangentSpaceMatrix[2] = float4( normal, 0.0f);
		tangentSpaceMatrix[3] = float4( 0.0f, 0.0f, 0.0f, 1.0f );
		//-1.0�`1.0�͈̔͂Ƀ}�b�s���O����B
		binSpaceNormal = (binSpaceNormal * 2.0f)- 1.0f;
		//�^���W�F���g�X�y�[�X���烏�[���h�X�y�[�X�̖@���ɕϊ�����B
		normal = tangentSpaceMatrix[0] * binSpaceNormal.x + tangentSpaceMatrix[1] * binSpaceNormal.y + tangentSpaceMatrix[2] * binSpaceNormal.z; 
		
	}
	
	
	float4 lig = DiffuseLight(normal);	
	
	if(g_isSpecularlight)
	{
		float3 eye=normalize(Eye-In.world.xyz);//�J��������I�u�W�F�N�g�ւ̕����H
		float3 L = -g_light.diffuseLightDir[0];//���C�g
		float3 N = normal.xyz;//�@��
		float3 R = -L+2.0f*dot(L,N)*N;
		lig+=pow(max(0.0f,dot(R,eye)),2.0f);//�ݏ�v�Z
		
	}
	
	if (g_isHasSpecularMap)
	{
		float3 spec=CalcSpecular(In.worldPos,normal);
		spec *= tex2D(g_specularMapSampler, In.Tex0).r;
		lig.xyz += spec;
	}
	
	color *= lig;
	
	
	
	float Zwrite = In.lightViewPos.z/In.lightViewPos.w;
	
	if(g_Reciver==1)
	{
		float2 shadowMapUV = In.lightViewPos.xy/In.lightViewPos.w;
		shadowMapUV *= float2(0.5f,-0.5f);
		
		shadowMapUV += float2(0.5f,0.5f);
		float x=tex2D(g_shadowMapTextureSampler,shadowMapUV).x;;
		if(Zwrite>x+0.005f){
			color *= 0.5f;
		}
	}
	
	return color;
}

/*!
* @brief	�s�N�Z���V�F�[�_�[�B
*/
float4 PSSkyMain(VS_OUTPUT In) : COLOR
{
	float3 normal = In.Normal;
	float4 color=texCUBE(g_cubeTexSampler,normal);
	return color;
}

/*!
 * @brief	�V���h�}�b�v�p�s�N�Z���V�F�[�_�[�H
 */
float4 PSShadowMain( VS_OUTPUT In ) : COLOR
{
	return float4(0.0f,0.0f,0.0f,1.0f);
}

/*!
 *@brief	�X�L�����胂�f���p�̃e�N�j�b�N�B
 */
technique SkinModel
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain(true);
        PixelShader = compile ps_3_0 PSMain();
    }
}
/*!
 *@brief	�X�L���Ȃ����f���p�̃e�N�j�b�N�B
 */
technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}

/*!
 *@brief	�V���h�E�}�b�v�X�L������p�̃e�N�j�b�N�B
 */
technique ShadowSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSShadowMain();
	}
}

/*!
 *@brief	�V���h�E�}�b�v�X�L���Ȃ��p�̃e�N�j�b�N�B
 */
technique ShadowNoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSShadowMain();
	}
}


technique SkyModel
{
	pass p0
	{
		VertexShader=compile vs_3_0 VSMain(false);
		PixelShader=compile ps_3_0 PSSkyMain();
	}
}