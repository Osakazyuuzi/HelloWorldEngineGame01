#ifndef ___BATTLE_MANAGER_H___
#define ___BATTLE_MANAGER_H___

#include "ComponentBase.h"
#include <memory>
#include <vector>
#include "ObjectBase.h"
#include <list>

class BattleManager : public ComponentBase
{
public:
	// コンストラクタ
	BattleManager();
	// デストラクタ
	~BattleManager();

	enum BattleMode {
		Mode_Standby,	// スタンバイ中
		Mode_Action,	// アクション中
		Mode_Select,	// 選択中
		Mode_Die,		// 倒した・倒された
		Mode_StatusSelect,	// 経験値配分選択中
		Mode_Max};

	enum ActionMode {
		Attack,		// 攻撃
		Special,	// 必殺技
		Skill,		// 特技
		Result,		// 降参
		Defence,	// 防御
		Counter,	// カウンター
		ActionMode_Max};	// 最大数

	void Start() override final;
	void Update() override final;

	// キャラクタを登録
	void AddCharacter(std::shared_ptr<ObjectBase> pCharacter);

	constexpr static std::float_t mc_ActionFrameNum = 120.0f;

private:

	BattleMode m_BattleMode;	// 現在のバトルモード
	ActionMode m_PlayerActionMode;	// 現在のプレイヤーアクションモード
	ActionMode m_EnemyActionMode;	// 現在のエネミーアクションモード

	std::shared_ptr<ObjectBase> m_PlayerCharacter;	// 自分のキャラクタ
	std::shared_ptr<ObjectBase> m_EnemyCharacter;	// 敵のキャラクタ

	std::float_t m_tick;	// フレームカウント

	std::shared_ptr<ObjectBase> m_ActionCharacter;	// アクション中キャラクタ
	std::shared_ptr<ObjectBase> m_DamageCharacter;	// 受けるキャラクタ

	std::list<std::shared_ptr<ObjectBase>> m_pSelectUI;

	bool m_bCounter;	// カウンターフラグ
};

#endif //!___BATTLE_MANAGER_H___