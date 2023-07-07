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
	// �֐߂̎��
	enum TERA_JOINT_INDEX {
		TERA_JOINT_BODY,
		TERA_JOINT_HEAD,
		TERA_JOINT_RIGHT_HAND,
		TERA_JOINT_LEFT_HAND,
		TERA_JOINT_RIGHT_LEG,
		TERA_JOINT_LEFT_LEG,
		TERA_JOINT_MAX
	};
	// �A�j���[�V�����̎��
	enum TERA_ANIM_INDEX {
		TERA_ANIM_NONE,		// ����
		TERA_ANIM_IDEL,		// ����
		TERA_ANIM_WALK,		// ����
		TERA_ANIM_RUN,		// ����
		TERA_ANIM_ATTACK,	// �U��
		TERA_ANIM_SPECIAL,	// �X�y�V����
		TERA_ANIM_DEFENCE,	// �h��
		TERA_ANIM_COUNTER,	// �J�E���^�[
		TERA_ANIM_MAX
	};		// �ő吔
public:
	// �R���X�g���N�^
	RonaAnimator() {}
	// �f�X�g���N�^
	~RonaAnimator() {}

	// �X�V
	void Update() override final;

	// �֐߂̏���������
	void InitJoint();

	// �֐߂�o�^
	void SetJoint(TERA_JOINT_INDEX _jointNum, std::shared_ptr<ObjectBase> _pJoint)
	{
		// �w��̈ʒu�Ƀ|�C���^���Z�b�g����
		m_pJoint[_jointNum] = _pJoint;
	}

	// �A�j���[�V�������Đ�
	void Play(TERA_ANIM_INDEX _animationNum)
	{
		// �֐߂�������
		InitJoint();
		// �Đ�����A�j���[�V�����ԍ����Z�b�g����
		m_PlayAnimationNum = _animationNum;
		// �t���[���J�E���g��0����n�߂�
		m_tick = 0;
	}

	// --- �Q�b�g�֐�
	const TERA_ANIM_INDEX& GetAnimNum() noexcept { return m_PlayAnimationNum; }

private:
	// �֐߃��X�g
	std::shared_ptr<ObjectBase> m_pJoint[TERA_JOINT_INDEX::TERA_JOINT_MAX];

	// �t���[���J�E���g
	std::int8_t m_tick;
	// �Đ��A�j���[�V�����ԍ�
	TERA_ANIM_INDEX m_PlayAnimationNum;
};

#endif //!___TERA_ANIMATOR_H___