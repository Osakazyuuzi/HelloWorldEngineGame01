#include "CameraBattle.h"
#include "ObjectBase.h"
#include "CameraObjBase.h"
#include "ObjectManager.h"
#include "Input.h"
#include "WinUtil.h"
#include "BattleManager.h"
#include "Define.h"

// コンストラクタ
CameraBattle::CameraBattle()
	: m_CursorPos({ 0.0f, 0.0f })
	, m_RotateSensitivity(0.3f)
	, m_radXZ(0.0f), m_radY(0.0f), m_radius(10.0f)
{

}

// デストラクタ
CameraBattle::~CameraBattle()
{
	m_pBattleBGMSource->SetVolume(0.0f);
	m_pBattleBGMSource->Stop();
	nhs::SAFE_DELETE(m_pBattleBGMData);
	nhs::SAFE_DELETE(m_pBattleBGMSource);
}

// 初期化
void CameraBattle::Start()
{
	// メインカメラにする
	static_cast<CameraObjBase*>(GetOwner())->ChangeToMainCamera();

	// バトル管理クラスを追加
	GetOwner()->AddComponent<BattleManager>();

	// ポインタを取得
	m_pTrans = GetOwner()->GetComponent<Transform>();

	//--- サウンド
	m_pBattleBGMData = CreateSound("Assets/Sound/SE/A5_06198.wav", true);
	m_pBattleBGMSource = nullptr;

	// サウンドを再生
	m_pBattleBGMSource = StartSound(m_pBattleBGMData);
	m_pBattleBGMSource->SetVolume(0.2f);

	// 距離を計測
	m_radius = ::sqrt(
		::pow(::abs(m_pTrans->GetPosition().x - m_LookPoint.x), 2) +
		::pow(::abs(m_pTrans->GetPosition().y - m_LookPoint.y), 2) +
		::pow(::abs(m_pTrans->GetPosition().z - m_LookPoint.z), 2)
	);

	//--- 角度を計測
	// Y角度
	m_radY = 2.922922f;	// エンカウントカメラの終了地点の角度
	
	// XZ角度
	// メインカメラの座標と注視点を取得する
	DirectX::XMFLOAT3 camPos = this->m_pTrans->GetPosition();
	DirectX::XMFLOAT3 camLook = this->m_LookPoint;
	// XY軸での二次元にベクトルを持ち込む
	camPos.y = 0.0f;
	camLook.y = 0.0f;
	// XMVECTORに変換
	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);
	DirectX::XMVECTOR vCamLook = DirectX::XMLoadFloat3(&camLook);
	// 注視点から座標へ向くベクトルを算出(後ろ)
	DirectX::XMVECTOR vBack;
	vBack = DirectX::XMVectorSubtract(vCamPos, vCamLook);
	vBack = DirectX::XMVector3Normalize(vBack);
	float radXZ = 0.0f;
	// X方向へのベクトル
	DirectX::XMFLOAT3 zVector = { 0.0f, 0.0f, -1.0f };
	// 内積とベクトルの長さを使ってcosθを求める
	DirectX::XMStoreFloat(&radXZ, DirectX::XMVector3Dot(DirectX::XMVector3Normalize(vBack), DirectX::XMLoadFloat3(&zVector)));
	// 内積から角度を求める
	radXZ = ::acos(radXZ);
	// ラジアン角からおなじみの角度に変更
	radXZ = DirectX::XMConvertToDegrees(radXZ);
	// 回転が右回転か左回転かを判別するために、外積で求める
	// 求めた外積のY成分がプラスだったら左回り。
	// 求めた外積のY成分がマイナスだったら右回り。
	DirectX::XMFLOAT3 rotateDirection;
	DirectX::XMStoreFloat3(&rotateDirection, DirectX::XMVector3Cross(DirectX::XMVector3Normalize(vBack), DirectX::XMLoadFloat3(&zVector)));
	if (rotateDirection.y > 0) radXZ = 180.0f + (180.0f - radXZ);
	m_radXZ = radXZ / 180 * 3.141592f;
}

// 更新
void CameraBattle::Update()
{
	// マウスの左ボタン
	if (IsKeyPress(VK_LBUTTON))
	{
		//=========================
		// Altキー＋マウス左ボタンで
		//  注視点を中心に回転する
		//=========================
		// マウスを右に
		if (m_CursorPos.x < GetCursorPos().x)
			m_radXZ -= (m_CursorPos.x - GetCursorPos().x) / 180 * 3.141592f * m_RotateSensitivity;
		// マウスを左に
		if (m_CursorPos.x > GetCursorPos().x)
			m_radXZ += (GetCursorPos().x - m_CursorPos.x) / 180 * 3.141592f * m_RotateSensitivity;
	}

	// 角度と距離、注視点からカメラの位置を計算
	GetOwner()->GetComponent<Transform>()->SetPosition({
	cosf(m_radY) * sinf(m_radXZ) * m_radius + m_LookPoint.x,
	sinf(m_radY) * m_radius + m_LookPoint.y,
	cosf(m_radY) * cosf(m_radXZ) * m_radius + m_LookPoint.z
		});
	// 現在のカーソル座標で更新
	m_CursorPos = GetCursorPos();
}

void CameraBattle::SetPosition(const DirectX::XMFLOAT3& _position)
{
	GetOwner()->GetComponent<Transform>()->SetPosition(_position);
}