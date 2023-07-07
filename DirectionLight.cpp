#include "DirectionLight.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "Transform.h"

// コンストラクタ
DirectionLight::DirectionLight()
{
}

// デストラクタ
DirectionLight::~DirectionLight()
{
	if (m_pLightBuf)
		delete m_pLightBuf;
}
void DirectionLight::Start()
{
	//--- 初期化
	m_pLightBuf = new ConstantBuffer();
	m_pLightBuf->Create(sizeof(Info));

	// ディレクションライトの向きをベクトルに変換
	m_Info.m_Direction = DirectX::XMFLOAT3(1.0f, 1.0f, 0.3f);
	DirectX::XMStoreFloat3(&m_Info.m_Direction, 
		DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&m_Info.m_Direction)));

	//--- ライトビュー行列を計算
	DirectX::XMMATRIX view;
	// ビュー行列を作成
	view = DirectX::XMMatrixLookAtLH(
		// 位置
		DirectX::XMVectorSet(
			-m_Info.m_Direction.x * 1000,
			-m_Info.m_Direction.y * 1000,
			-m_Info.m_Direction.z * 1000,
			0.0f),
		// 注視点
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		// アップベクトル
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	// 転置する
	view = DirectX::XMMatrixTranspose(view);
	// XMFLOAT4x4に変換
	DirectX::XMStoreFloat4x4(&m_Info.m_matView, view);

	//--- ライト投影行列を計算
//	DirectX::XMFLOAT4X4 fProj;
//	DirectX::XMStoreFloat4x4(&fProj,
//		DirectX::XMMatrixTranspose(
//			DirectX::XMMatrixOrthographicOffCenterLH(
//				-640.0f,	// 画面左端の座標
//				640.0f,		// 画面右端の座標
//				-360.0f,	// 画面下端の座標
//				360.0f,		// 画面上端の座標
//				0.3f,		// Z値で写す範囲の最小値
//				1000.0f		// Z値で写す範囲の最大値
//			)
//		));
//	m_Info.m_matProj = fProj;

	DirectX::XMMATRIX proj;
	// プロジェクション行列を作成
	proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(60.0f), 16.0f / 9.0f, 0.3f, 1000.0f);
	// 転置する
	proj = DirectX::XMMatrixTranspose(proj);
	// XMFLOAT4x4に変換
	DirectX::XMStoreFloat4x4(&m_Info.m_matProj, proj);
}

void DirectionLight::SetLight()
{
	//ライトの情報を書込み頂点シェーダに送る
	m_pLightBuf->Write(&m_Info);
	m_pLightBuf->BindVS(1);
}