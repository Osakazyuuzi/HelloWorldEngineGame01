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

// �f�B���N�V�������C�g�̏����󂯓n���o�b�t�@
cbuffer DirectionLightCb : register(b1)
{
	// �f�B���N�V�������C�g�̏��
	float4 direction;  // ����
	// ���C�g�̃r���[�s��
	float4x4 lightView;
	// ���C�g�̃v���W�F�N�V�����s��
	float4x4 lightProj;
};

cbuffer ModelInfoCb : register(b2)
{
	// ���f���̐F
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

	// �J�����̖ڐ��ɂ��ϊ�
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);

//	// ���C�g�̖ڐ��ɂ��ϊ�
//	pos = mul(pos, world);
//	pos = mul(pos, lightView);
//	vout.ZCalcTex = mul(pos, lightProj);

	nor = mul(vin.normal, world).xyz;
	nor = normalize(nor);

	col = saturate(dot(nor, (float3)direction));
	col = col * 0.5f + 0.5f;

	vout.color = float4(col * color.r, col * color.g, col * color.b, 1.0f);

	// UV���W�̎󂯓n��
	vout.uv = vin.uv;

	return vout;
}
