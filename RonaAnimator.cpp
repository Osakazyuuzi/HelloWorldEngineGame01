#include "RonaAnimator.h"
#include "Transform.h"

// 関節を初期化
void RonaAnimator::InitJoint()
{
	// 変更用ポインタ
	std::shared_ptr<Transform> pTrans;

	// 全ての関節の角度と座標を初期化
	for (int jointNum = 0; jointNum < TERA_JOINT_INDEX::TERA_JOINT_MAX; jointNum++)
	{
		pTrans = m_pJoint[jointNum]->GetComponent<Transform>();
		pTrans->SetAngle({ 0.0f, 0.0f, 0.0f });
		pTrans->SetPosition(pTrans->GetJointPos());
	}
}

// 更新
void RonaAnimator::Update()
{
	//--- 現在のアニメーションの種類によって分岐
	switch (m_PlayAnimationNum) {
		// 何もしていないのアニメーションの場合
	case TERA_ANIM_INDEX::TERA_ANIM_NONE:
		break;
		// 立ちアニメーションの場合
	case TERA_ANIM_INDEX::TERA_ANIM_IDEL:
		if (0 <= m_tick < 60) {
			// 頭を上下させる
			m_pJoint[TERA_JOINT_HEAD]->GetComponent<Transform>()->SetPosition({
				m_pJoint[TERA_JOINT_HEAD]->GetComponent<Transform>()->GetJointPos().x,
				m_pJoint[TERA_JOINT_HEAD]->GetComponent<Transform>()->GetJointPos().y + std::sinf(m_tick / 10) * 0.02f,
				m_pJoint[TERA_JOINT_HEAD]->GetComponent<Transform>()->GetJointPos().z });
			// 右手を上下させる（回転によって上下を表現）
			m_pJoint[TERA_JOINT_RIGHT_HAND]->GetComponent<Transform>()->SetAngle({
				std::sinf(m_tick / 10) * -10, 0.0f, 0.0f });
			// 左手を上下させる（回転によって上下を表現）
			m_pJoint[TERA_JOINT_LEFT_HAND]->GetComponent<Transform>()->SetAngle({
				std::sinf(m_tick / 10) * 10, 0.0f, 0.0f });
		}
		else {
			// ループするアニメーションのためループさせる
			m_tick = 0;
		}
		break;
		// 歩きアニメーションの場合
	case TERA_ANIM_INDEX::TERA_ANIM_WALK:
		if (0 <= m_tick < 60) {
			// 体の上下の振り幅
			float SwingWidth = abs(std::sinf(m_tick / 5) * 0.04f);
			// 体を上下させる
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetPosition({
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().x,
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().y + SwingWidth,
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().z });
			// 正面方向のベクトル
			DirectX::XMFLOAT3 forwardDirection = GetOwner()->GetComponent<Transform>()->GetVectorForword();
			// 右足を前後に動かす
			m_pJoint[TERA_JOINT_RIGHT_LEG]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 5) * 50,
				forwardDirection.y * std::sinf(m_tick / 5) * 50,
				forwardDirection.z * std::sinf(m_tick / 5) * 50
				});
			// 左足を前後に動かす
			m_pJoint[TERA_JOINT_LEFT_LEG]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 5) * -50,
				forwardDirection.y * std::sinf(m_tick / 5) * -50,
				forwardDirection.z * std::sinf(m_tick / 5) * -50
				});
			// 右手を前後に動かす
			m_pJoint[TERA_JOINT_RIGHT_HAND]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 5) * -50,
				forwardDirection.y * std::sinf(m_tick / 5) * -50,
				forwardDirection.z * std::sinf(m_tick / 5) * -50
				});
			// 左手を前後に動かす
			m_pJoint[TERA_JOINT_LEFT_HAND]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 5) * 50,
				forwardDirection.y * std::sinf(m_tick / 5) * 50,
				forwardDirection.z * std::sinf(m_tick / 5) * 50
				});
		}
		else {
			// ループするアニメーションのためループさせる
			m_tick = 0;
		}
		break;
		// 走りアニメーションの場合
	case TERA_ANIM_INDEX::TERA_ANIM_RUN:
		if (0 <= m_tick < 60) {
			// 体の上下の振り幅
			float SwingWidth = abs(std::sinf(m_tick / 2) * 0.05f);
			// 体を上下させる
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetPosition({
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().x,
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().y + SwingWidth,
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().z });
			// 正面方向のベクトル
			DirectX::XMFLOAT3 forwardDirection = GetOwner()->GetComponent<Transform>()->GetVectorForword();
			// 右足を前後に動かす
			m_pJoint[TERA_JOINT_RIGHT_LEG]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 2) * 50,
				forwardDirection.y * std::sinf(m_tick / 2) * 50,
				forwardDirection.z * std::sinf(m_tick / 2) * 50
				});
			// 左足を前後に動かす
			m_pJoint[TERA_JOINT_LEFT_LEG]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 2) * -50,
				forwardDirection.y * std::sinf(m_tick / 2) * -50,
				forwardDirection.z * std::sinf(m_tick / 2) * -50
				});
			// 右手を前後に動かす
			m_pJoint[TERA_JOINT_RIGHT_HAND]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 2) * -50,
				forwardDirection.y * std::sinf(m_tick / 2) * -50,
				forwardDirection.z * std::sinf(m_tick / 2) * -50
				});
			// 左手を前後に動かす
			m_pJoint[TERA_JOINT_LEFT_HAND]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 2) * 50,
				forwardDirection.y * std::sinf(m_tick / 2) * 50,
				forwardDirection.z * std::sinf(m_tick / 2) * 50
				});
		}
		else {
			// ループするアニメーションのためループさせる
			m_tick = 0;
		}
		break;

		// 攻撃アニメーションの場合
	case TERA_ANIM_INDEX::TERA_ANIM_ATTACK:
		if (0 <= m_tick < 60) {
			// 体の上下の振り幅
			float SwingWidth = abs(std::sinf(m_tick / 5) * 50);
			// 体を上下させる
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetAngle({
				0.0f,
				0.0f + SwingWidth,
				0.0f });
		}
		else {
			// ループするアニメーションのためループさせる
			m_tick = 0;
		}
		break;
		// スぺシャルアニメーションの場合
	case TERA_ANIM_INDEX::TERA_ANIM_SPECIAL:
		if (0 <= m_tick < 60) {
			// 体を上下させる
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetAngle({
				0.0f,
				0.0f,
				0.0f + m_tick * 5000 });
		}
		else {
			// ループするアニメーションのためループさせる
			m_tick = 0;
		}
		break;
		// スぺシャルアニメーションの場合
	case TERA_ANIM_INDEX::TERA_ANIM_DEFENCE:
		if (0 <= m_tick < 60) {
			// 右手を上下させる（回転によって上下を表現）
			m_pJoint[TERA_JOINT_RIGHT_HAND]->GetComponent<Transform>()->SetAngle({
				std::sinf(m_tick) * -100, 0.0f, 0.0f });
			// 左手を上下させる（回転によって上下を表現）
			m_pJoint[TERA_JOINT_LEFT_HAND]->GetComponent<Transform>()->SetAngle({
				std::sinf(m_tick) * 100, 0.0f, 0.0f });
		}
		else {
			// ループするアニメーションのためループさせる
			m_tick = 0;
		}
		break;
		// スぺシャルアニメーションの場合
	case TERA_ANIM_INDEX::TERA_ANIM_COUNTER:
		if (0 <= m_tick < 60) {
			// 体を上下させる
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetAngle({
				0.0f,
				0.0f + m_tick * 5000,
				0.0f });
		}
		else {
			// ループするアニメーションのためループさせる
			m_tick = 0;
		}
		break;
	}

	// カウントする
	m_tick++;
}