#include "RonaController.h"
#include "Status.h"
#include "RonaAnimator.h"
#include "Define.h"
#include "Input.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "AABBCollider.h"
#include "CameraPlayer.h"
#include "SceneManager.h"

#include "CameraObjBase.h"
#include "CameraEncounter.h"

// コンストラクタ
RonaController::RonaController()
	: m_lateRotY(0.0f)
	, m_TargetRotY(0.0f)
{

}

// デストラクタ
RonaController::~RonaController()
{
	nhs::SAFE_DELETE(m_pWalkSEData);
	nhs::SAFE_DELETE(m_pWalkSESource);
}

// 初期化
void RonaController::Start()
{
	// 所属オブジェクトのアドレスを取得
	m_pOwner = static_cast<std::shared_ptr<ObjectBase>>(GetOwner());

	// コンポーネントのアドレスを取得
	m_pStatus = m_pOwner->GetComponent<Status>();
	m_pAnimtor = m_pOwner->GetComponent<RonaAnimator>();

	//--- サウンド
	m_pWalkSEData = CreateSound("Assets/Sound/SE/A5_01015.wav", false);
	m_pWalkSESource = nullptr;

	//--- 当たり判定をとるオブジェクトを設定
	GetOwner()->GetComponent<AABBCollider>()->SetTouchOBB(TagName::Ground);
}

// 更新
void RonaController::Update()
{
	// Playerタグのオブジェクトの座標を取得
	DirectX::XMFLOAT3 PlayerPos = ObjectManager::FindObjectWithTag(TagName::Player)->GetComponent<Transform>()->GetPosition();
	// ターゲットまでのベクトルを算出
	DirectX::XMVECTOR vTargetVector =
		DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&PlayerPos), DirectX::XMLoadFloat3(&GetOwner()->GetComponent<Transform>()->GetPosition()));
	// ベクトルを正規化
	vTargetVector = DirectX::XMVector3Normalize(vTargetVector);

	// -X方向へのベクトル(モデルの正面方向のベクトル)
	DirectX::XMFLOAT3 zVector = { -1.0f, 0.0f, 0.0f };
	// 内積とベクトルの長さを使ってcosθを求める
	DirectX::XMStoreFloat(&m_TargetRotY, DirectX::XMVector3Dot(DirectX::XMVector3Normalize(vTargetVector), DirectX::XMLoadFloat3(&zVector)));
	// 内積から角度を求める
	m_TargetRotY = ::acos(m_TargetRotY);
	// ラジアン角からおなじみの角度に変更
	m_TargetRotY = DirectX::XMConvertToDegrees(m_TargetRotY);
	// 回転が右回転か左回転かを判別するために、外積で求める
	// 求めた外積のY成分がプラスだったら左回り。
	// 求めた外積のY成分がマイナスだったら右回り。
	DirectX::XMFLOAT3 rotateDirection;
	DirectX::XMStoreFloat3(&rotateDirection, DirectX::XMVector3Cross(DirectX::XMVector3Normalize(vTargetVector), DirectX::XMLoadFloat3(&zVector)));
	if (rotateDirection.y > 0) m_TargetRotY = 180.0f + (180.0f - m_TargetRotY);

	// 二つの間の角度が180°超えていた場合、逆回転の方が速いため、補正
	if (abs(m_lateRotY - m_TargetRotY) >= 180.0f)
		if (m_TargetRotY < 0.0f) m_TargetRotY = (int)m_TargetRotY + 360;
		else if (m_TargetRotY >= 0.0f) m_TargetRotY = (int)m_TargetRotY - 360;
	// 180°を超えたもしくは、-180°以下になったときに範囲内に補正する
	if (m_lateRotY < -180)  m_lateRotY = ((int)(fabs(m_lateRotY) + 180) % 360 - 180) * -1.0f;
	if (180 <= m_lateRotY) m_lateRotY = (int)(m_lateRotY + 180) % 360 - 180;
	// 遅れてついていく場合の角度を計算し適応する
	m_lateRotY = (m_TargetRotY - m_lateRotY) * 0.05f + m_lateRotY;
	GetOwner()->GetComponent<Transform>()->SetAngle({ 0.0f, m_TargetRotY,0.0f });

	//--- 探索モードの場合
	if (SceneManager::GetSceneMode() == SceneName::GameField) {
		if (m_TargetRotY - 5.0f < m_lateRotY && m_lateRotY < m_TargetRotY + 5.0f) {
			// 立ちアニメーションでなければ立ちアニメーションへ
			if (m_pAnimtor->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL)
				m_pAnimtor->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL);
		}
		else {
			// 歩きアニメーションを再生中でなければ
			if (m_pAnimtor->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_WALK)
				// 歩きアニメーションにする
				m_pAnimtor->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_WALK);
		}
	}
	//--- バトルモードの場合
	else if (SceneManager::GetSceneMode() == SceneName::GameBattle) {
//		// 立ちアニメーションでなければ立ちアニメーションへ
//		if (m_pAnimtor->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL)
//			m_pAnimtor->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL);
		}
}

// 当たり判定
void RonaController::OnCollisionEnter(ObjectBase* pObject)
{
	// フィールドと当たったときの処理
	if (pObject->GetTag() == TagName::Ground) {
		// Y軸の加速度をゼロに
		this->GetOwner()->GetComponent<Rigidbody>()->SetAccele({
			this->GetOwner()->GetComponent<Rigidbody>()->GetAccele().x,
			0.0f,
			this->GetOwner()->GetComponent<Rigidbody>()->GetAccele().z
			});

		// --- めり込んだ位置からY方向に戻し距離だけオフセットする
		float offsetPosY =
			pObject->GetComponent<AABBCollider>()->GetPrimitive().p.y +
			pObject->GetComponent<AABBCollider>()->GetPrimitive().hl.y +
			this->GetOwner()->GetComponent<AABBCollider>()->GetPrimitive().hl.y;
		this->GetOwner()->GetComponent<Transform>()->SetPosition({
			this->GetOwner()->GetComponent<Transform>()->GetPosition().x,
			offsetPosY,
			this->GetOwner()->GetComponent<Transform>()->GetPosition().z
			});
	}
}

// 当たり判定
void RonaController::OnCollisionStay(ObjectBase* pObject)
{
	// フィールドと当たったときの処理
	if (pObject->GetTag() == TagName::Ground) {
		// Y軸の加速度をゼロに
		this->GetOwner()->GetComponent<Rigidbody>()->SetAccele({
			this->GetOwner()->GetComponent<Rigidbody>()->GetAccele().x,
			0.0f,
			this->GetOwner()->GetComponent<Rigidbody>()->GetAccele().z
			});

		// --- めり込んだ位置からY方向に戻し距離だけオフセットする
		float offsetPosY =
			pObject->GetComponent<AABBCollider>()->GetPrimitive().p.y +
			pObject->GetComponent<AABBCollider>()->GetPrimitive().hl.y +
			this->GetOwner()->GetComponent<AABBCollider>()->GetPrimitive().hl.y;
		this->GetOwner()->GetComponent<Transform>()->SetPosition({
			this->GetOwner()->GetComponent<Transform>()->GetPosition().x,
			offsetPosY,
			this->GetOwner()->GetComponent<Transform>()->GetPosition().z
			});
	}
}