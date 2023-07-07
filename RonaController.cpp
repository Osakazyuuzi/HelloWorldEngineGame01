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

// �R���X�g���N�^
RonaController::RonaController()
	: m_lateRotY(0.0f)
	, m_TargetRotY(0.0f)
{

}

// �f�X�g���N�^
RonaController::~RonaController()
{
	nhs::SAFE_DELETE(m_pWalkSEData);
	nhs::SAFE_DELETE(m_pWalkSESource);
}

// ������
void RonaController::Start()
{
	// �����I�u�W�F�N�g�̃A�h���X���擾
	m_pOwner = static_cast<std::shared_ptr<ObjectBase>>(GetOwner());

	// �R���|�[�l���g�̃A�h���X���擾
	m_pStatus = m_pOwner->GetComponent<Status>();
	m_pAnimtor = m_pOwner->GetComponent<RonaAnimator>();

	//--- �T�E���h
	m_pWalkSEData = CreateSound("Assets/Sound/SE/A5_01015.wav", false);
	m_pWalkSESource = nullptr;

	//--- �����蔻����Ƃ�I�u�W�F�N�g��ݒ�
	GetOwner()->GetComponent<AABBCollider>()->SetTouchOBB(TagName::Ground);
}

// �X�V
void RonaController::Update()
{
	// Player�^�O�̃I�u�W�F�N�g�̍��W���擾
	DirectX::XMFLOAT3 PlayerPos = ObjectManager::FindObjectWithTag(TagName::Player)->GetComponent<Transform>()->GetPosition();
	// �^�[�Q�b�g�܂ł̃x�N�g�����Z�o
	DirectX::XMVECTOR vTargetVector =
		DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&PlayerPos), DirectX::XMLoadFloat3(&GetOwner()->GetComponent<Transform>()->GetPosition()));
	// �x�N�g���𐳋K��
	vTargetVector = DirectX::XMVector3Normalize(vTargetVector);

	// -X�����ւ̃x�N�g��(���f���̐��ʕ����̃x�N�g��)
	DirectX::XMFLOAT3 zVector = { -1.0f, 0.0f, 0.0f };
	// ���ςƃx�N�g���̒������g����cos�Ƃ����߂�
	DirectX::XMStoreFloat(&m_TargetRotY, DirectX::XMVector3Dot(DirectX::XMVector3Normalize(vTargetVector), DirectX::XMLoadFloat3(&zVector)));
	// ���ς���p�x�����߂�
	m_TargetRotY = ::acos(m_TargetRotY);
	// ���W�A���p���炨�Ȃ��݂̊p�x�ɕύX
	m_TargetRotY = DirectX::XMConvertToDegrees(m_TargetRotY);
	// ��]���E��]������]���𔻕ʂ��邽�߂ɁA�O�ςŋ��߂�
	// ���߂��O�ς�Y�������v���X�������獶���B
	// ���߂��O�ς�Y�������}�C�i�X��������E���B
	DirectX::XMFLOAT3 rotateDirection;
	DirectX::XMStoreFloat3(&rotateDirection, DirectX::XMVector3Cross(DirectX::XMVector3Normalize(vTargetVector), DirectX::XMLoadFloat3(&zVector)));
	if (rotateDirection.y > 0) m_TargetRotY = 180.0f + (180.0f - m_TargetRotY);

	// ��̊Ԃ̊p�x��180�������Ă����ꍇ�A�t��]�̕����������߁A�␳
	if (abs(m_lateRotY - m_TargetRotY) >= 180.0f)
		if (m_TargetRotY < 0.0f) m_TargetRotY = (int)m_TargetRotY + 360;
		else if (m_TargetRotY >= 0.0f) m_TargetRotY = (int)m_TargetRotY - 360;
	// 180���𒴂����������́A-180���ȉ��ɂȂ����Ƃ��ɔ͈͓��ɕ␳����
	if (m_lateRotY < -180)  m_lateRotY = ((int)(fabs(m_lateRotY) + 180) % 360 - 180) * -1.0f;
	if (180 <= m_lateRotY) m_lateRotY = (int)(m_lateRotY + 180) % 360 - 180;
	// �x��Ă��Ă����ꍇ�̊p�x���v�Z���K������
	m_lateRotY = (m_TargetRotY - m_lateRotY) * 0.05f + m_lateRotY;
	GetOwner()->GetComponent<Transform>()->SetAngle({ 0.0f, m_TargetRotY,0.0f });

	//--- �T�����[�h�̏ꍇ
	if (SceneManager::GetSceneMode() == SceneName::GameField) {
		if (m_TargetRotY - 5.0f < m_lateRotY && m_lateRotY < m_TargetRotY + 5.0f) {
			// �����A�j���[�V�����łȂ���Η����A�j���[�V������
			if (m_pAnimtor->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL)
				m_pAnimtor->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL);
		}
		else {
			// �����A�j���[�V�������Đ����łȂ����
			if (m_pAnimtor->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_WALK)
				// �����A�j���[�V�����ɂ���
				m_pAnimtor->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_WALK);
		}
	}
	//--- �o�g�����[�h�̏ꍇ
	else if (SceneManager::GetSceneMode() == SceneName::GameBattle) {
//		// �����A�j���[�V�����łȂ���Η����A�j���[�V������
//		if (m_pAnimtor->GetAnimNum() != RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL)
//			m_pAnimtor->Play(RonaAnimator::TERA_ANIM_INDEX::TERA_ANIM_IDEL);
		}
}

// �����蔻��
void RonaController::OnCollisionEnter(ObjectBase* pObject)
{
	// �t�B�[���h�Ɠ��������Ƃ��̏���
	if (pObject->GetTag() == TagName::Ground) {
		// Y���̉����x���[����
		this->GetOwner()->GetComponent<Rigidbody>()->SetAccele({
			this->GetOwner()->GetComponent<Rigidbody>()->GetAccele().x,
			0.0f,
			this->GetOwner()->GetComponent<Rigidbody>()->GetAccele().z
			});

		// --- �߂荞�񂾈ʒu����Y�����ɖ߂����������I�t�Z�b�g����
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

// �����蔻��
void RonaController::OnCollisionStay(ObjectBase* pObject)
{
	// �t�B�[���h�Ɠ��������Ƃ��̏���
	if (pObject->GetTag() == TagName::Ground) {
		// Y���̉����x���[����
		this->GetOwner()->GetComponent<Rigidbody>()->SetAccele({
			this->GetOwner()->GetComponent<Rigidbody>()->GetAccele().x,
			0.0f,
			this->GetOwner()->GetComponent<Rigidbody>()->GetAccele().z
			});

		// --- �߂荞�񂾈ʒu����Y�����ɖ߂����������I�t�Z�b�g����
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