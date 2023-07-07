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

// �R���X�g���N�^
BattleManager::BattleManager()
	: m_BattleMode(BattleMode::Mode_Standby)
	, m_tick(0.0f)
	, m_bCounter(false)
{
}

// �f�X�g���N�^
BattleManager::~BattleManager()
{
	
}

// ������
void BattleManager::Start()
{
	m_PlayerCharacter = ObjectManager::FindObjectWithTag(TagName::Player);
	m_EnemyCharacter = ObjectManager::FindObjectWithTag(TagName::Enemy);


	//---- �G���[�Ή�
	if (m_PlayerCharacter == nullptr) {
		MessageBox(NULL, "�����L�����N�^�[���o�g���ɎQ�����Ă��܂���B", "�G���[", MB_OK | MB_ICONERROR);
	}
	if (m_EnemyCharacter == nullptr) {
		MessageBox(NULL, "�G�L�����N�^�[���o�g���ɎQ�����Ă��܂���B", "�G���[", MB_OK | MB_ICONERROR);
	}

	// �v���C���[
	if (!m_PlayerCharacter->GetComponent<Status>()) {
		MessageBox(NULL, "�o�g���ɎQ�������v���C���[�L�����N�^�[��Status�R���|�[�l���g�������Ă��܂���B", "�G���[", MB_OK | MB_ICONERROR);
	}
	// �G
	if (!m_EnemyCharacter->GetComponent<Status>()) {
		MessageBox(NULL, "�o�g���ɎQ�������G�L�����N�^�[��Status�R���|�[�l���g�������Ă��܂���B", "�G���[", MB_OK | MB_ICONERROR);
	}
}

// �X�V
void BattleManager::Update()
{
	// ���[�h�ɂ���ĕ���
	switch (m_BattleMode) {
		// �X�^���o�C���[�h�̏ꍇ
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

		// �����A�j���[�V�������Đ����łȂ����
		if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL)
			// �����A�j���[�V�����ɂ���
			m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL);

		// �����A�j���[�V�������Đ����łȂ����
		if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL)
			// �����A�j���[�V�����ɂ���
			m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL);
		//--- �v���C���[
		// �A�N�V�����Q�[�W�𑝉����A���܂���������Ƃ�
		if (m_PlayerCharacter->GetComponent<Status>()->AddActionGage()) {
			// �A�N�V��������L�����N�^���Z�b�g����
			m_ActionCharacter = m_PlayerCharacter;
			// �A�N�V��������L�����N�^���Z�b�g����
			m_DamageCharacter = m_EnemyCharacter;
			// �I�����[�h�ɂ���
			m_BattleMode = BattleMode::Mode_Select;
			// �A�N�V�����t���[���𐔂��Ȃ���
			m_tick = 0;
			// �A�N�V�����Q�[�W�����𒆒f����
			return;
		}
		//--- �G
		// �A�N�V�����Q�[�W�𑝉����A���܂���������Ƃ�
		if (m_EnemyCharacter->GetComponent<Status>()->AddActionGage()) {
			// �A�N�V��������L�����N�^���Z�b�g����
			m_ActionCharacter = m_EnemyCharacter;
			// �A�N�V��������L�����N�^���Z�b�g����
			m_DamageCharacter = m_PlayerCharacter;
			// �I�����[�h�ɂ���
			m_BattleMode = BattleMode::Mode_Select;
			// �A�N�V�����t���[���𐔂��Ȃ���
			m_tick = 0;
			// �A�N�V�����Q�[�W�����𒆒f����
			return;
		}
		// �J�E���g����
		m_tick++;
		// �A�N�V�������[�h�̏ꍇ
	case BattleMode::Mode_Action:
		// �A�N�V�������[�h���Ԃ𒴉߂�����
		if (m_tick > mc_ActionFrameNum) {
			// �X�^���o�C���[�h�ɕύX
			m_BattleMode = BattleMode::Mode_Standby;
			if (m_PlayerCharacter->GetComponent<Status>()->GetHp() <= 0) m_BattleMode = BattleMode::Mode_Die;
			if (m_EnemyCharacter->GetComponent<Status>()->GetHp() <= 0) m_BattleMode = BattleMode::Mode_StatusSelect;
			// �I��
			return;
		}
		if (!m_pSelectUI.empty()) {
			for (auto it = m_pSelectUI.begin(); it != m_pSelectUI.end(); ++it)
				ObjectManager::RemoveObject((*it));
		}

		switch (m_PlayerActionMode) {
		// �U���̏ꍇ
		case ActionMode::Attack:

			// �����A�j���[�V�������Đ����łȂ����
			if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK)
				// �����A�j���[�V�����ɂ���
				m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK);

			// �U���A�N�V�����̃^�C�~���O�ɂȂ�����
			if (m_tick == 60) {
				if (m_EnemyActionMode == ActionMode::Defence) {
					// �����A�j���[�V�������Đ����łȂ����
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE)
						// �����A�j���[�V�����ɂ���
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE);

					// �_���[�W���󂯂�L�����N�^�ɗ^����
					m_DamageCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)) / 2);
				}
				else
				{
					// �����A�j���[�V�������Đ����łȂ����
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER)
						// �����A�j���[�V�����ɂ���
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER);

					// �_���[�W���󂯂�L�����N�^�ɗ^����
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
		// �K�E�Z�̏ꍇ
		case ActionMode::Special:

			// �����A�j���[�V�������Đ����łȂ����
			if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL)
				// �����A�j���[�V�����ɂ���
				m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL);


			// �K�E�Z�A�N�V�����̃^�C�~���O�ɂȂ�����
			if (m_tick == 60) {
				if (m_EnemyActionMode == ActionMode::Defence) {

					// �����A�j���[�V�������Đ����łȂ����
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE)
						// �����A�j���[�V�����ɂ���
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE);

					// �_���[�W���󂯂�L�����N�^�ɗ^����
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
					// �����A�j���[�V�������Đ����łȂ����
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER)
						// �����A�j���[�V�����ɂ���
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER);

					// �A�N�V���������L�����N�^�ɗ^����
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
		// �h��̏ꍇ
		case ActionMode::Defence:

			// �����A�j���[�V�������Đ����łȂ����
			if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE)
				// �����A�j���[�V�����ɂ���
				m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_DEFENCE);

			// �U���A�N�V�����̃^�C�~���O�ɂȂ�����
			if (m_tick == 60) {
				// �G���U�����ǂ���
				if (m_EnemyActionMode == ActionMode::Attack) {
					// �����A�j���[�V�������Đ����łȂ����
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK)
						// �����A�j���[�V�����ɂ���
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK);

					// �_���[�W���󂯂�L�����N�^�ɗ^����
					m_DamageCharacter->GetComponent<Status>()->Damage((
						(m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff()
							/ m_DamageCharacter->GetComponent<Status>()->GetDefense() * m_DamageCharacter->GetComponent<Status>()->GetDefenseBuff())
						+ (m_ActionCharacter->GetComponent<Status>()->GetAttack() * m_ActionCharacter->GetComponent<Status>()->GetAttackBuff() * 0.2f)) / 2);
				}
				else if (m_EnemyActionMode == ActionMode::Special)
				{
					// �����A�j���[�V�������Đ����łȂ����
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL)
						// �����A�j���[�V�����ɂ���
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL);
					// �A�N�V���������L�����N�^�ɗ^����
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
		// �J�E���^�[�̏ꍇ
		case ActionMode::Counter:

			// �����A�j���[�V�������Đ����łȂ����
			if (m_PlayerCharacter->GetComponent<TeraAnimator>()->GetAnimNum() != TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER)
				// �����A�j���[�V�����ɂ���
				m_PlayerCharacter->GetComponent<TeraAnimator>()->Play(TeraAnimator::TERA_ANIM_INDEX::TERA_ANIM_COUNTER);


			// �U���A�N�V�����̃^�C�~���O�ɂȂ�����
			if (m_tick == 60) {
				// �����A�j���[�V�������Đ����łȂ����
				if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK)
					// �����A�j���[�V�����ɂ���
					m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_ATTACK);
				// �G���U�����ǂ���
				if (m_EnemyActionMode == ActionMode::Attack) {
					// �_���[�W���󂯂�L�����N�^�ɗ^����
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
					// �����A�j���[�V�������Đ����łȂ����
					if (m_EnemyCharacter->GetComponent<RonaAnimator>()->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL)
						// �����A�j���[�V�����ɂ���
						m_EnemyCharacter->GetComponent<RonaAnimator>()->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_SPECIAL);
					// �A�N�V���������L�����N�^�ɗ^����
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
		// �J�E���g����
		m_tick++;
		break;
	// �I�����[�h�̏ꍇ
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
				// �A�N�V�������[�h�ɕύX
				m_BattleMode = BattleMode::Mode_Action;
				m_PlayerActionMode = ActionMode::Attack;
			}
			else if (IsKeyTrigger('A')) {
				// �A�N�V�������[�h�ɕύX
				m_BattleMode = BattleMode::Mode_Action;
				m_PlayerActionMode = ActionMode::Special;
			}
			else if (IsKeyTrigger('S')) {
				SceneManager::LoadScene(SceneName::SceneTitle);
			}

			// �G�̑I�����������_���Ō��߂�
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
				// �A�N�V�������[�h�ɕύX
				m_BattleMode = BattleMode::Mode_Action;
				m_PlayerActionMode = ActionMode::Defence;
			}
			else if (IsKeyTrigger('A')) {
				// �A�N�V�������[�h�ɕύX
				m_BattleMode = BattleMode::Mode_Action;
				m_PlayerActionMode = ActionMode::Counter;
				m_bCounter = true;
			}
			else if (IsKeyTrigger('S')) {
				SceneManager::LoadScene(SceneName::SceneTitle);
			}

			// �G�̑I�����������_���Ō��߂�
			m_EnemyActionMode = ActionMode(rand() % 2);
			if (rand() % 50 != 0) {
				m_EnemyActionMode = ActionMode::Attack;
			}
		}
		m_tick++;
		break;
	// ���ʃ��[�h�̏ꍇ
	case BattleMode::Mode_Die:
		SceneManager::LoadScene(SceneName::SceneLose);
		break;
	// �|�������[�h�̏ꍇ
	case BattleMode::Mode_StatusSelect:
		SceneManager::LoadScene(SceneName::SceneWin);
		break;
	}
	return;
}

// �L�����N�^��o�^
void BattleManager::AddCharacter(std::shared_ptr<ObjectBase> pCharacter) {
	pCharacter->GetComponent<Status>()->GetCharacterType() == Status::CharacterType::Player ?
		m_PlayerCharacter = pCharacter : m_EnemyCharacter = pCharacter;
}