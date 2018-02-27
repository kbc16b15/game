/*!
 *@brief	スプライト用シェーダー。
 */
#include "Common.h" 

struct VS_INPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

float4x4 mWorld;		//ワールド行列。
float4 uvRect;			//UV矩形。
float alpha;			//不透明度。

texture g_tex;
sampler TextureSampler = 
sampler_state
{
    Texture = <g_tex>;
    MipFilter = NONE;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = mul(In.pos, mWorld);
	Out.uv	= uvRect.xy * (1.0f - In.uv) + uvRect.zw * (In.uv);
	return Out;
}
float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	float4 color = tex2D( TextureSampler, In.uv );
	color.a *= alpha;
	return color;
}

technique SpriteTexture
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMain();
		PixelShader		= compile ps_3_0 PSMain();
	}
}