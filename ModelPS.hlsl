struct PS_IN {
	float4 pos      : SV_POSITION;
	float2 uv       : TEXCOORD0;
	float4 ZCalcTex : TEXCOORD1;
	float4 color	: COLOR0;
};

Texture2D tex : register(t0);

SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
//	// ���C�g�ڐ��ɂ��Z�l�̎Z�o
//	float Zvalue = pin.ZCalcTex.z / pin.ZCalcTex.w;
//
//	// �ˉe��Ԃ�XY���W���e�N�X�`�����W�ɕϊ�
//	float2 TransTexCoord;
//	TransTexCoord.x = (1.0f + pin.ZCalcTex.x / pin.ZCalcTex.w)*0.5f;
//	TransTexCoord.y = (1.0f - pin.ZCalcTex.y / pin.ZCalcTex.w)*0.5f;
//
//	// ���A��Z�l���o
//	float SM_Z = tex.Sample(samp, TransTexCoord).x;
//
//	// �Z�o�_���V���h�E�}�b�v��Z�l�����傫����Ήe�Ɣ��f
//	if (Zvalue > SM_Z + 0.0005f) {
//		pin.color.rgb = pin.color.rgb * 0.5f;
//	}

	return tex.Sample(samp, pin.uv) * pin.color;
}