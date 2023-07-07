#include "BattleManager.h"
#include "Status.h"
#include "WinUtil.h"
#include "ObjectManager.h"
#include "Input.h"
#include "TeraIcon.h"
#include "RonaIcon.h"
#include "ActionGage.h"
#include "RonaHPBarObj.h"
#include "TeraHPBar.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "SceneManager.h"
#include "TeraAnimator.h"
#include "RonaAnimator.h"

// コンストラクタ
BattleManager::BattleManager()
	: m_BattleMode(BattleMode::Mode_Standby)
	, m_tick(0.0f)
	, m_bCounter(false)
{
}

// デストラクタ
BattleManager::~BattleManager()
{
	
}

// 初期化
void BattleManager::Start()
{
	m_PlayerCharacter = ObjectManager::FindObjectWithTag(TagName::Player);
	m_EnemyCharacter = ObjectManager::FindObjectWithTag(TagName::Enemy);


	//---- エラー対応
	if (m_PlayerCharacter == nullptr) {
		MessageBox(NULL, "味方キャラクターがバトルに参加していません。", "エラー", MB_OK | MB_ICONERROR);
	}
	if (m_EnemyCharacter == nullptr) {
		MessageBox(NULL, "敵キャラクターがバトルに参加していません。", "エラー", MB_OK | MB_ICONERROR);
	}

	// プレイヤー
	if (!m_PlayerCharacter->GetComponent<Status>()) {
		MessageBox(NULL, "バトルに参加したプレイヤーキャラクターがStatusコンポーネントを持っていません。", "エラー", MB_OK | MB_ICONERROR);
	}
	// 敵
	if (!m_EnemyCharacter->GetComponent<Status>()) {
		MessageBox(NULL, "バトルに参加した敵キャラクターがStatusコンポーネントを持っていません。", "エラー", MB_OK | MB_ICONERROR);
	}
}

// 更新
void BattleManager::Update()
{
	// モードによって分岐
	switch (m_BattleMode) {
		// スタンバイモードの場合
	case BattleMode::Mode_Standby:
		if (m_tick == 0) {
			std::shared_ptr<ObjectBase> pObj;
			std::shared_ptr<SpriteRenderer> pSpriteRenderer;
			std::shared_ptr<Transform> pTransform;
			ObjectManager::CreateObject<ActionGage>("UI_ActionGage");
			ObjectManager::CreateObject<RonaIcon>("UI_Rona_ActionIcon");
			ObjectManager::CreateObject<TeraIcon>("UI_Tera_ActionIcon");

			ObjectManager::CreateObject<RonaHPBar>("Billboard_Rona_HPBar");
			ObjectManager::CreateObject<TeraHPBar>("UI_Tera_HPBar");

			pObj = ObjectManager::CreateObject<UI>("UI_Tera_Icon");
			pSpriteRenderer = pObj->GetComponent<SpriteRenderer>();
			pTransform = pObj->GetComponent<Transform>();
			pSpriteRenderer->LoadTexture("Assets/Texture/TeraIcon.png");
			pSpriteRenderer->SetSize(200, 200);
			pObj->SetLayerNum(1);
			pTransform->SetPosition({ -530.0f, -250.0f, 0.0f });
		}

		// 立ちアニメーションを再生中でなければ
		if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL)
			// 立ちアニメーションにする
			m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL);

		// 立ちアニメーションを再生中でなければ
		if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL)
			// 立ちアニメーションにする
			m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL);
		//--- プレイヤー
		// アクションゲージを増加し、溜まった判定をとる
		if (m_PlayerCharacter->GetComponent<Status>()->AddActionGage()) {
			// アクションするキャラクタをセットする
			m_ActionCharacter = m_PlayerCharacter;
			// アクションするキャラクタをセットする
			m_DamageCharacter = m_EnemyCharacter;
			// 選択モードにする
			m_BattleMode = BattleMode::Mode_Select;
			// アクションフレームを数えなおす
			m_tick = 0;
			// アクションゲージ増加を中断する
			return;
		}
		//--- 敵
		// アクションゲージを増加し、溜まった判定をとる
		if (m_EnemyCharacter->GetComponent<Status>()->AddActionGage()) {
			// アクションするキャラクタをセットする
			m_ActionCharacter = m_EnemyCharacter;
			// アクションするキャラクタをセットする
			m_DamageCharacter = m_PlayerCharacter;
			// 選択モードにする
			m_BattleMode = BattleMode::Mode_Select;
			// アクションフレームを数えなおす
			m_tick = 0;
			// アクションゲージ増加を中断する
			return;
		}
		// カウントする
		m_tick++;
		// アクションモードの場合
	case BattleMode::Mode_Action:
		// アクションモード時間を超過したら
		if (m_tick > mc_ActionFrameNum) {
			// スタンバイモードに変更
			m_BattleMode = BattleMode::Mode_Standby;
			if (m_PlayerCharacter->GetComponent<Status>()->GetHp() <= 0) m_BattleMode = BattleMode::Mode_Die;
			if (m_EnemyCharacter->GetComponent<Status>()->GetHp() <= 0) m_BattleMode = BattleMode::Mode_StatusSelect;
			// 終了
			return;
		}
		if (!m_pSelectUI.empty()) {
			for (auto it = m_pSelectUI.begin(); it != m_pSelectUI.end(); ++it)
				ObjectManager::RemoveObject((*it));
		}

		switch (m_PlayerActionMode) {
		// 攻撃の場合
		case ActionMode::Attack:

			// 立ちアニメーションを再生中でなければ
			if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK)
				// 立ちアニメーションにする
				m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK);

			// 攻撃アクションのタイミングになったら
			if (m_tick == 60) {
				if (m_EnemyActionMode == ActionMode::Defence) {
					// 立ちアニメーションを再生中でなければ
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE)
						// 立ちアニメーションにする
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE);

					// ダメージを受けるキャラクタに与える
					m_DamageCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)) / 2);
				}
				else
				{
					// 立ちアニメーションを再生中でなければ
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER)
						// 立ちアニメーションにする
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER);

					// ダメージを受けるキャラクタに与える
					m_DamageCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)));
				}

				std::shared_ptr<ObjectBase> pObj;
				for (int i = 0; i < 30; i++) {
					pObj = ObjectManager::CreateObject<Particle>("particle");
					pObj->GetComponent<Transform>()->SetPosition(m_DamageCharacter->GetComponent<Transform>()->GetPosition());
					pObj->GetComponent<Rigidbody>()->SetAccele({
						((rand() % 100) - 50) * 0.01f,
						((rand() % 100) - 50) * 0.01f,
						((rand() % 100) - 50) * 0.01f });
				}
			}
			break;
		// 必殺技の場合
		case ActionMode::Special:

			// 立ちアニメーションを再生中でなければ
			if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL)
				// 立ちアニメーションにする
				m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL);


			// 必殺技アクションのタイミングになったら
			if (m_tick == 60) {
				if (m_EnemyActionMode == ActionMode::Defence) {

					// 立ちアニメーションを再生中でなければ
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE)
						// 立ちアニメーションにする
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE);

					// ダメージを受けるキャラクタに与える
					m_DamageCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)) * 2);

					std::shared_ptr<ObjectBase> pObj;
					for (int i = 0; i < 30; i++) {
						pObj = ObjectManager::CreateObject<Particle>("particle");
						pObj->GetComponent<Transform>()->SetPosition(m_DamageCharacter->GetComponent<Transform>()->GetPosition());
						pObj->GetComponent<Rigidbody>()->SetAccele({
							((rand() % 100) - 50) * 0.01f,
							((rand() % 100) - 50) * 0.01f,
							((rand() % 100) - 50) * 0.01f });
					}
				}
				else
				{
					// 立ちアニメーションを再生中でなければ
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER)
						// 立ちアニメーションにする
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER);

					// アクションしたキャラクタに与える
					m_ActionCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)) * 2);

					std::shared_ptr<ObjectBase> pObj;
					for (int i = 0; i < 30; i++) {
						pObj = ObjectManager::CreateObject<Particle>("particle");
						pObj->GetComponent<Transform>()->SetPosition(m_ActionCharacter->GetComponent<Transform>()->GetPosition());
						pObj->GetComponent<Rigidbody>()->SetAccele({
							((rand() % 100) - 50) * 0.01f,
							((rand() % 100) - 50) * 0.01f,
							((rand() % 100) - 50) * 0.01f });
					}
				}
			}
			break;
		// 防御の場合
		case ActionMode::Defence:

			// 立ちアニメーションを再生中でなければ
			if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE)
				// 立ちアニメーションにする
				m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE);

			// 攻撃アクションのタイミングになったら
			if (m_tick == 60) {
				// 敵が攻撃かどうか
				if (m_EnemyActionMode == ActionMode::Attack) {
					// 立ちアニメーションを再生中でなければ
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK)
						// 立ちアニメーションにする
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK);

					// ダメージを受けるキャラクタに与える
					m_DamageCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)) / 2);
				}
				else if (m_EnemyActionMode == ActionMode::Special)
				{
					// 立ちアニメーションを再生中でなければ
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL)
						// 立ちアニメーションにする
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL);
					// アクションしたキャラクタに与える
					m_DamageCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)) * 2);
				}

				std::shared_ptr<ObjectBase> pObj;
				for (int i = 0; i < 30; i++) {
					pObj = ObjectManager::CreateObject<Particle>("particle");
					pObj->GetComponent<Transform>()->SetPosition(m_DamageCharacter->GetComponent<Transform>()->GetPosition());
					pObj->GetComponent<Rigidbody>()->SetAccele({
						((rand() % 100) - 50) * 0.01f,
						((rand() % 100) - 50) * 0.01f,
						((rand() % 100) - 50) * 0.01f });
				}
			}
			break;
		// カウンターの場合
		case ActionMode::Counter:

			// 立ちアニメーションを再生中でなければ
			if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER)
				// 立ちアニメーションにする
				m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER);


			// 攻撃アクションのタイミングになったら
			if (m_tick == 60) {
				// 立ちアニメーションを再生中でなければ
				if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK)
					// 立ちアニメーションにする
					m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK);
				// 敵が攻撃かどうか
				if (m_EnemyActionMode == ActionMode::Attack) {
					// ダメージを受けるキャラクタに与える
					m_DamageCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)));

					std::shared_ptr<ObjectBase> pObj;
					for (int i = 0; i < 30; i++) {
						pObj = ObjectManager::CreateObject<Particle>("particle");
						pObj->GetComponent<Transform>()->SetPosition(m_DamageCharacter->GetComponent<Transform>()->GetPosition());
						pObj->GetComponent<Rigidbody>()->SetAccele({
							((rand() % 100) - 50) * 0.01f,
							((rand() % 100) - 50) * 0.01f,
							((rand() % 100) - 50) * 0.01f });
					}
				}
				else if (m_EnemyActionMode == ActionMode::Special)
				{
					// 立ちアニメーションを再生中でなければ
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL)
						// 立ちアニメーションにする
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL);
					// アクションしたキャラクタに与える
					m_ActionCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)) * 2);

					std::shared_ptr<ObjectBase> pObj;
					for (int i = 0; i < 30; i++) {
						pObj = ObjectManager::CreateObject<Particle>("particle");
						pObj->GetComponent<Transform>()->SetPosition(m_ActionCharacter->GetComponent<Transform>()->GetPosition());
						pObj->GetComponent<Rigidbody>()->SetAccele({
							((rand() % 100) - 50) * 0.01f,
							((rand() % 100) - 50) * 0.01f,
							((rand() % 100) - 50) * 0.01f });
					}
				}
			}
			break;
		default:
			break;
		}
		// カウントする
		m_tick++;
		break;
	// 選択モードの場合
	case BattleMode::Mode_Select:

		if (m_ActionCharacter == m_PlayerCharacter) {
			if (m_tick == 0) {
				std::shared_ptr<ObjectBase> pObj;
				std::shared_ptr<SpriteRenderer> pSpriteRenderer;
				std::shared_ptr<Transform> pTransform;
				pObj = ObjectManager::CreateObject<UI>("UI_Tera_Icon");
				pSpriteRenderer = pObj->GetComponent<SpriteRenderer>();
				pTransform = pObj->GetComponent<Transform>();
				pSpriteRenderer->LoadTexture("Assets/Texture/SelectAttack.png");
				pSpriteRenderer->SetSize(300, 200);
				pObj->SetLayerNum(1);
				pTransform->SetPosition({ 430.0f, -200.0f, 0.0f });
				m_pSelectUI.push_back(pObj);
				pObj = ObjectManager::CreateObject<UI>("UI_Tera_Icon");
				pSpriteRenderer = pObj->GetComponent<SpriteRenderer>();
				pTransform = pObj->GetComponent<Transform>();
				pSpriteRenderer->LoadTexture("Assets/Texture/SelectMoji.png");
				pSpriteRenderer->SetSize(300, 200);
				pObj->SetLayerNum(2);
				pTransform->SetPosition({ 430.0f, -140.0f, 0.0f });
				m_pSelectUI.push_back(pObj);
			}
			if (IsKeyTrigger('D')) {
				// アクションモードに変更
				m_BattleMode = BattleMode::Mode_Action;
				m_PlayerActionMode = ActionMode::Attack;
			}
			else if (IsKeyTrigger('A')) {
				// アクションモードに変更
				m_BattleMode = BattleMode::Mode_Action;
				m_PlayerActionMode = ActionMode::Special;
			}
			else if (IsKeyTrigger('S')) {
				SceneManager::LoadScene(SceneName::SceneTitle);
			}

			// 敵の選択肢をランダムで決める
			m_EnemyActionMode = ActionMode(rand() % 2 + 4);
			if (rand() % 50 != 0) {
				m_EnemyActionMode = ActionMode::Counter;
			}
		}
		else
		{
			if (m_tick == 0) {
				std::shared_ptr<ObjectBase> pObj;
				std::shared_ptr<SpriteRenderer> pSpriteRenderer;
				std::shared_ptr<Transform> pTransform;
				pObj = ObjectManager::CreateObject<UI>("UI_Tera_Icon");
				pSpriteRenderer = pObj->GetComponent<SpriteRenderer>();
				pTransform = pObj->GetComponent<Transform>();
				pSpriteRenderer->LoadTexture("Assets/Texture/SelectDefense.png");
				pSpriteRenderer->SetSize(300, 200);
				pObj->SetLayerNum(1);
				pTransform->SetPosition({ 430.0f, -200.0f, 0.0f });
				m_pSelectUI.push_back(pObj);
				pObj = ObjectManager::CreateObject<UI>("UI_Tera_Icon");
				pSpriteRenderer = pObj->GetComponent<SpriteRenderer>();
				pTransform = pObj->GetComponent<Transform>();
				pSpriteRenderer->LoadTexture("Assets/Texture/SelectMoji.png");
				pSpriteRenderer->SetSize(300, 200);
				pObj->SetLayerNum(2);
				pTransform->SetPosition({ 430.0f, -140.0f, 0.0f });
				m_pSelectUI.push_back(pObj);
			}
			m_bCounter = false;
			if (IsKeyTrigger('D')) {
				// アクションモードに変更
				m_BattleMode = BattleMode::Mode_Action;
				m_PlayerActionMode = ActionMode::Defence;
			}
			else if (IsKeyTrigger('A')) {
				// アクションモードに変更
				m_BattleMode = BattleMode::Mode_Action;
				m_PlayerActionMode = ActionMode::Counter;
				m_bCounter = true;
			}
			else if (IsKeyTrigger('S')) {
				SceneManager::LoadScene(SceneName::SceneTitle);
			}

			// 敵の選択肢をランダムで決める
			m_EnemyActionMode = ActionMode(rand() % 2);
			if (rand() % 50 != 0) {
				m_EnemyActionMode = ActionMode::Attack;
			}
		}
		m_tick++;
		break;
	// 死ぬモードの場合
	case BattleMode::Mode_Die:
		SceneManager::LoadScene(SceneName::SceneLose);
		break;
	// 倒したモードの場合
	case BattleMode::Mode_StatusSelect:
		SceneManager::LoadScene(SceneName::SceneWin);
		break;
	}
	return;
}

// キャラクタを登録
void BattleManager::AddCharacter(std::shared_ptr<ObjectBase> pCharacter) {
	pCharacter->GetComponent<Status>()->GetCharacterType() == Status::CharacterType::Player ?
		m_PlayerCharacter = pCharacter : m_EnemyCharacter = pCharacter;
}