/*!
 * @brief	スキンモデルシェーダー。(4ボーンスキニング)
 */

#include "LightingFunction.h"

//スキン行列。
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;
float		g_numBone;			//骨の数。

float4x4	g_viewMatrix;			//!ビュー
float4x4	g_projectionMatrix;		//!プロジェクション行列
float4x4	g_worldMatrix;			//!<ワールド行列。
float4x4	g_rotationMatrix;		//!<回転行列。
float4x4	g_viewMatrixRotInv;		//!<カメラの回転行列の逆行列。

float4x4 g_viewlightMatrix;
float4x4 g_projlightMatrix;

bool g_Reciver;
bool g_isSpecularlight;
float g_Scroll;
int g_MoveDir;

float3 Eye;				//カメラ座標
bool g_isHasNormalMap;			//法線マップ保持している？
int g_isHasSpecularMap;		//スペキュラマップ保持？
texture g_diffuseTexture;		//ディフューズテクスチャ。
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

texture g_shadowMapTexture;		//シャドウマップテクスチャ。
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

//法線マップ
texture g_normalTexture;		//法線マップ。
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

//スペキュラマップ
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

//キューブマップ
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
 * @brief	入力頂点
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
    float3	Tangent			: TANGENT;		//接ベクトル
    float3  Tex0            : TEXCOORD0;
    //float4  color		:COLOR0;
   //float2 uv			:TEXCOORD4;
};

/*!
 * @brief	出力頂点。
 */
struct VS_OUTPUT
{

	float4  Pos     		: POSITION;
    float3  Normal			: NORMAL;
    float2  Tex0   			: TEXCOORD0;
    float3	Tangent			: TEXCOORD1;	//接ベクトル
    float3 world			: TEXCOORD2;	//ワールドの変換座標
    float4 lightViewPos 		: TEXCOORD3;
 
    //float4  color		:COLOR0;
    float3 worldPos			:TEXCOORD4;

};
/*!
 *@brief	ワールド座標とワールド法線をスキン行列から計算する。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;
	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//ブレンドレート。
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
 *@brief	ワールド座標とワールド法線を計算。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	Normal = mul(In.Normal, g_rotationMatrix );
	Tangent = mul(In.Tangent, g_rotationMatrix );
}
/*!
 *@brief	頂点シェーダー。
 *@param[in]	In			入力頂点。
 *@param[in]	hasSkin		スキンあり？
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	
	if(hasSkin){
		//スキンあり。
	    CalcWorldPosAndNormalFromSkinMatrix( In, Pos, Normal, Tangent );

	}else{
		//スキンなし。
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
 * @brief	ピクセルシェーダー。
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
		//法線マップがある。
		float3 tangent = normalize(In.Tangent);
		float3 binSpaceNormal = tex2D( g_normalMapSampler, In.Tex0);
		float4x4 tangentSpaceMatrix;
		//法線とタンジェントから従法線を求める
		float3 biNormal = normalize( cross( tangent, normal) );
		//タンジェントスペースからワールドスペースに変換する行列を求める。
		tangentSpaceMatrix[0] = float4( tangent, 0.0f);
		tangentSpaceMatrix[1] = float4( biNormal, 0.0f);
		tangentSpaceMatrix[2] = float4( normal, 0.0f);
		tangentSpaceMatrix[3] = float4( 0.0f, 0.0f, 0.0f, 1.0f );
		//-1.0～1.0の範囲にマッピングする。
		binSpaceNormal = (binSpaceNormal * 2.0f)- 1.0f;
		//タンジェントスペースからワールドスペースの法線に変換する。
		normal = tangentSpaceMatrix[0] * binSpaceNormal.x + tangentSpaceMatrix[1] * binSpaceNormal.y + tangentSpaceMatrix[2] * binSpaceNormal.z; 
		
	}
	
	
	float4 lig = DiffuseLight(normal);	
	
	if(g_isSpecularlight)
	{
		float3 eye=normalize(Eye-In.world.xyz);//カメラからオブジェクトへの方向？
		float3 L = -g_light.diffuseLightDir[0];//ライト
		float3 N = normal.xyz;//法線
		float3 R = -L+2.0f*dot(L,N)*N;
		lig+=pow(max(0.0f,dot(R,eye)),2.0f);//累乗計算
		
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
* @brief	ピクセルシェーダー。
*/
float4 PSSkyMain(VS_OUTPUT In) : COLOR
{
	float3 normal = In.Normal;
	float4 color=texCUBE(g_cubeTexSampler,normal);
	return color;
}

/*!
 * @brief	シャドマップ用ピクセルシェーダー？
 */
float4 PSShadowMain( VS_OUTPUT In ) : COLOR
{
	return float4(0.0f,0.0f,0.0f,1.0f);
}

/*!
 *@brief	スキンありモデル用のテクニック。
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
 *@brief	スキンなしモデル用のテクニック。
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
 *@brief	シャドウマップスキンあり用のテクニック。
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
 *@brief	シャドウマップスキンなし用のテクニック。
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