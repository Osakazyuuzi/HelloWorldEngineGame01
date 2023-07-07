struct VS_IN
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};
struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 ZCalcTex : TEXCOORD1;
	float4 color : COLOR0;
};

cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};

// ディレクションライトの情報を受け渡すバッファ
cbuffer DirectionLightCb : register(b1)
{
	// ディレクションライトの情報
	float4 direction;  // 向き
	// ライトのビュー行列
	float4x4 lightView;
	// ライトのプロジェクション行列
	float4x4 lightProj;
};

cbuffer ModelInfoCb : register(b2)
{
	// モデルの色
	float3 color;
}

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;
	float3 nor;
	float  col;
	float4x4 mat;
	float4 pos;

	vout.pos = float4(vin.pos, 1.0f);
	pos = float4(vin.pos, 1.0f);

	// カメラの目線による変換
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);

//	// ライトの目線による変換
//	pos = mul(pos, world);
//	pos = mul(pos, lightView);
//	vout.ZCalcTex = mul(pos, lightProj);

	nor = mul(vin.normal, world).xyz;
	nor = normalize(nor);

	col = saturate(dot(nor, (float3)direction));
	col = col * 0.5f + 0.5f;

	vout.color = float4(col * color.r, col * color.g, col * color.b, 1.0f);

	// UV座標の受け渡し
	vout.uv = vin.uv;

	return vout;
}
