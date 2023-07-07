#include "RonaAnimator.h"
#include "Transform.h"

// �֐߂�������
void RonaAnimator::InitJoint()
{
	// �ύX�p�|�C���^
	std::shared_ptr<Transform> pTrans;

	// �S�Ă̊֐߂̊p�x�ƍ��W��������
	for (int jointNum = 0; jointNum < TERA_JOINT_INDEX::TERA_JOINT_MAX; jointNum++)
	{
		pTrans = m_pJoint[jointNum]->GetComponent<Transform>();
		pTrans->SetAngle({ 0.0f, 0.0f, 0.0f });
		pTrans->SetPosition(pTrans->GetJointPos());
	}
}

// �X�V
void RonaAnimator::Update()
{
	//--- ���݂̃A�j���[�V�����̎�ނɂ���ĕ���
	switch (m_PlayAnimationNum) {
		// �������Ă��Ȃ��̃A�j���[�V�����̏ꍇ
	case TERA_ANIM_INDEX::TERA_ANIM_NONE:
		break;
		// �����A�j���[�V�����̏ꍇ
	case TERA_ANIM_INDEX::TERA_ANIM_IDEL:
		if (0 <= m_tick < 60) {
			// �����㉺������
			m_pJoint[TERA_JOINT_HEAD]->GetComponent<Transform>()->SetPosition({
				m_pJoint[TERA_JOINT_HEAD]->GetComponent<Transform>()->GetJointPos().x,
				m_pJoint[TERA_JOINT_HEAD]->GetComponent<Transform>()->GetJointPos().y + std::sinf(m_tick / 10) * 0.02f,
				m_pJoint[TERA_JOINT_HEAD]->GetComponent<Transform>()->GetJointPos().z });
			// �E����㉺������i��]�ɂ���ď㉺��\���j
			m_pJoint[TERA_JOINT_RIGHT_HAND]->GetComponent<Transform>()->SetAngle({
				std::sinf(m_tick / 10) * -10, 0.0f, 0.0f });
			// ������㉺������i��]�ɂ���ď㉺��\���j
			m_pJoint[TERA_JOINT_LEFT_HAND]->GetComponent<Transform>()->SetAngle({
				std::sinf(m_tick / 10) * 10, 0.0f, 0.0f });
		}
		else {
			// ���[�v����A�j���[�V�����̂��߃��[�v������
			m_tick = 0;
		}
		break;
		// �����A�j���[�V�����̏ꍇ
	case TERA_ANIM_INDEX::TERA_ANIM_WALK:
		if (0 <= m_tick < 60) {
			// �̂̏㉺�̐U�蕝
			float SwingWidth = abs(std::sinf(m_tick / 5) * 0.04f);
			// �̂��㉺������
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetPosition({
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().x,
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().y + SwingWidth,
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().z });
			// ���ʕ����̃x�N�g��
			DirectX::XMFLOAT3 forwardDirection = GetOwner()->GetComponent<Transform>()->GetVectorForword();
			// �E����O��ɓ�����
			m_pJoint[TERA_JOINT_RIGHT_LEG]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 5) * 50,
				forwardDirection.y * std::sinf(m_tick / 5) * 50,
				forwardDirection.z * std::sinf(m_tick / 5) * 50
				});
			// ������O��ɓ�����
			m_pJoint[TERA_JOINT_LEFT_LEG]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 5) * -50,
				forwardDirection.y * std::sinf(m_tick / 5) * -50,
				forwardDirection.z * std::sinf(m_tick / 5) * -50
				});
			// �E���O��ɓ�����
			m_pJoint[TERA_JOINT_RIGHT_HAND]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 5) * -50,
				forwardDirection.y * std::sinf(m_tick / 5) * -50,
				forwardDirection.z * std::sinf(m_tick / 5) * -50
				});
			// �����O��ɓ�����
			m_pJoint[TERA_JOINT_LEFT_HAND]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 5) * 50,
				forwardDirection.y * std::sinf(m_tick / 5) * 50,
				forwardDirection.z * std::sinf(m_tick / 5) * 50
				});
		}
		else {
			// ���[�v����A�j���[�V�����̂��߃��[�v������
			m_tick = 0;
		}
		break;
		// ����A�j���[�V�����̏ꍇ
	case TERA_ANIM_INDEX::TERA_ANIM_RUN:
		if (0 <= m_tick < 60) {
			// �̂̏㉺�̐U�蕝
			float SwingWidth = abs(std::sinf(m_tick / 2) * 0.05f);
			// �̂��㉺������
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetPosition({
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().x,
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().y + SwingWidth,
				m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->GetJointPos().z });
			// ���ʕ����̃x�N�g��
			DirectX::XMFLOAT3 forwardDirection = GetOwner()->GetComponent<Transform>()->GetVectorForword();
			// �E����O��ɓ�����
			m_pJoint[TERA_JOINT_RIGHT_LEG]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 2) * 50,
				forwardDirection.y * std::sinf(m_tick / 2) * 50,
				forwardDirection.z * std::sinf(m_tick / 2) * 50
				});
			// ������O��ɓ�����
			m_pJoint[TERA_JOINT_LEFT_LEG]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 2) * -50,
				forwardDirection.y * std::sinf(m_tick / 2) * -50,
				forwardDirection.z * std::sinf(m_tick / 2) * -50
				});
			// �E���O��ɓ�����
			m_pJoint[TERA_JOINT_RIGHT_HAND]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 2) * -50,
				forwardDirection.y * std::sinf(m_tick / 2) * -50,
				forwardDirection.z * std::sinf(m_tick / 2) * -50
				});
			// �����O��ɓ�����
			m_pJoint[TERA_JOINT_LEFT_HAND]->GetComponent<Transform>()->SetAngle({
				forwardDirection.x * std::sinf(m_tick / 2) * 50,
				forwardDirection.y * std::sinf(m_tick / 2) * 50,
				forwardDirection.z * std::sinf(m_tick / 2) * 50
				});
		}
		else {
			// ���[�v����A�j���[�V�����̂��߃��[�v������
			m_tick = 0;
		}
		break;

		// �U���A�j���[�V�����̏ꍇ
	case TERA_ANIM_INDEX::TERA_ANIM_ATTACK:
		if (0 <= m_tick < 60) {
			// �̂̏㉺�̐U�蕝
			float SwingWidth = abs(std::sinf(m_tick / 5) * 50);
			// �̂��㉺������
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetAngle({
				0.0f,
				0.0f + SwingWidth,
				0.0f });
		}
		else {
			// ���[�v����A�j���[�V�����̂��߃��[�v������
			m_tick = 0;
		}
		break;
		// �X�؃V�����A�j���[�V�����̏ꍇ
	case TERA_ANIM_INDEX::TERA_ANIM_SPECIAL:
		if (0 <= m_tick < 60) {
			// �̂��㉺������
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetAngle({
				0.0f,
				0.0f,
				0.0f + m_tick * 5000 });
		}
		else {
			// ���[�v����A�j���[�V�����̂��߃��[�v������
			m_tick = 0;
		}
		break;
		// �X�؃V�����A�j���[�V�����̏ꍇ
	case TERA_ANIM_INDEX::TERA_ANIM_DEFENCE:
		if (0 <= m_tick < 60) {
			// �E����㉺������i��]�ɂ���ď㉺��\���j
			m_pJoint[TERA_JOINT_RIGHT_HAND]->GetComponent<Transform>()->SetAngle({
				std::sinf(m_tick) * -100, 0.0f, 0.0f });
			// ������㉺������i��]�ɂ���ď㉺��\���j
			m_pJoint[TERA_JOINT_LEFT_HAND]->GetComponent<Transform>()->SetAngle({
				std::sinf(m_tick) * 100, 0.0f, 0.0f });
		}
		else {
			// ���[�v����A�j���[�V�����̂��߃��[�v������
			m_tick = 0;
		}
		break;
		// �X�؃V�����A�j���[�V�����̏ꍇ
	case TERA_ANIM_INDEX::TERA_ANIM_COUNTER:
		if (0 <= m_tick < 60) {
			// �̂��㉺������
			m_pJoint[TERA_JOINT_BODY]->GetComponent<Transform>()->SetAngle({
				0.0f,
				0.0f + m_tick * 5000,
				0.0f });
		}
		else {
			// ���[�v����A�j���[�V�����̂��߃��[�v������
			m_tick = 0;
		}
		break;
	}

	// �J�E���g����
	m_tick++;
}