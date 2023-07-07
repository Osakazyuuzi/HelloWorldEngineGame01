#ifndef ___RONA_ANIMATOR_H___
#define ___RONA_ANIMATOR_H___

#include "ComponentBase.h"
#include "ObjectBase.h"
#include <memory>
#include <vector>
#include <cstdint>

class RonaAnimator : public ComponentBase
{
public:
	// 関節の種類
	enum TERA_JOINT_INDEX {
		TERA_JOINT_BODY,
		TERA_JOINT_HEAD,
		TERA_JOINT_RIGHT_HAND,
		TERA_JOINT_LEFT_HAND,
		TERA_JOINT_RIGHT_LEG,
		TERA_JOINT_LEFT_LEG,
		TERA_JOINT_MAX
	};
	// アニメーションの種類
	enum TERA_ANIM_INDEX {
		TERA_ANIM_NONE,		// 無し
		TERA_ANIM_IDEL,		// 立ち
		TERA_ANIM_WALK,		// 歩き
		TERA_ANIM_RUN,		// 走り
		TERA_ANIM_ATTACK,	// 攻撃
		TERA_ANIM_SPECIAL,	// スペシャル
		TERA_ANIM_DEFENCE,	// 防御
		TERA_ANIM_COUNTER,	// カウンター
		TERA_ANIM_MAX
	};		// 最大数
public:
	// コンストラクタ
	RonaAnimator() {}
	// デストラクタ
	~RonaAnimator() {}

	// 更新
	void Update() override final;

	// 関節の情報を初期化
	void InitJoint();

	// 関節を登録
	void SetJoint(TERA_JOINT_INDEX _jointNum, std::shared_ptr<ObjectBase> _pJoint)
	{
		// 指定の位置にポインタをセットする
		m_pJoint[_jointNum] = _pJoint;
	}

	// アニメーションを再生
	void Play(TERA_ANIM_INDEX _animationNum)
	{
		// 関節を初期化
		InitJoint();
		// 再生するアニメーション番号をセットする
		m_PlayAnimationNum = _animationNum;
		// フレームカウントを0から始める
		m_tick = 0;
	}

	// --- ゲット関数
	const TERA_ANIM_INDEX& GetAnimNum() noexcept { return m_PlayAnimationNum; }

private:
	// 関節リスト
	std::shared_ptr<ObjectBase> m_pJoint[TERA_JOINT_INDEX::TERA_JOINT_MAX];

	// フレームカウント
	std::int8_t m_tick;
	// 再生アニメーション番号
	TERA_ANIM_INDEX m_PlayAnimationNum;
};

#endif //!___TERA_ANIMATOR_H___