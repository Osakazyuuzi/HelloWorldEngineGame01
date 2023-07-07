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
	// �R���X�g���N�^
	BattleManager();
	// �f�X�g���N�^
	~BattleManager();

	enum BattleMode {
		Mode_Standby,	// �X�^���o�C��
		Mode_Action,	// �A�N�V������
		Mode_Select,	// �I��
		Mode_Die,		// �|�����E�|���ꂽ
		Mode_StatusSelect,	// �o���l�z���I��
		Mode_Max};

	enum ActionMode {
		Attack,		// �U��
		Special,	// �K�E�Z
		Skill,		// ���Z
		Result,		// �~�Q
		Defence,	// �h��
		Counter,	// �J�E���^�[
		ActionMode_Max};	// �ő吔

	void Start() override final;
	void Update() override final;

	// �L�����N�^��o�^
	void AddCharacter(std::shared_ptr<ObjectBase> pCharacter);

	constexpr static std::float_t mc_ActionFrameNum = 120.0f;

private:

	BattleMode m_BattleMode;	// ���݂̃o�g�����[�h
	ActionMode m_PlayerActionMode;	// ���݂̃v���C���[�A�N�V�������[�h
	ActionMode m_EnemyActionMode;	// ���݂̃G�l�~�[�A�N�V�������[�h

	std::shared_ptr<ObjectBase> m_PlayerCharacter;	// �����̃L�����N�^
	std::shared_ptr<ObjectBase> m_EnemyCharacter;	// �G�̃L�����N�^

	std::float_t m_tick;	// �t���[���J�E���g

	std::shared_ptr<ObjectBase> m_ActionCharacter;	// �A�N�V�������L�����N�^
	std::shared_ptr<ObjectBase> m_DamageCharacter;	// �󂯂�L�����N�^

	std::list<std::shared_ptr<ObjectBase>> m_pSelectUI;

	bool m_bCounter;	// �J�E���^�[�t���O
};

#endif //!___BATTLE_MANAGER_H___