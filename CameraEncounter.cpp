#include "CameraEncounter.h"
#include "ObjectBase.h"
#include "CameraObjBase.h"
#include "ObjectManager.h"
#include <memory>
#include "CameraBattle.h"

// �R���X�g���N�^
CameraEncounter::CameraEncounter()
	: m_tick(0.0f)
	, m_IsEnd(false)
{

}

// �f�X�g���N�^
CameraEncounter::~CameraEncounter()
{

}

// ������
void CameraEncounter::Start()
{
	// ���C���J�����ɂ���
	static_cast<CameraObjBase*>(GetOwner())->ChangeToMainCamera();

	// �|�C���^���擾
	m_pTrans = GetOwner()->GetComponent<Transform>();
	// ����_�̍��W���Z�o
	m_ControlPosition1.x = 
		m_pTrans->GetPosition().x + (m_LookPoint.x - m_pTrans->GetPosition().x) * mc_controlPos1Per;
	m_ControlPosition1.y =
		m_pTrans->GetPosition().y + (m_LookPoint.y - m_pTrans->GetPosition().y) * mc_controlPos1Per;
	m_ControlPosition1.z =
		m_pTrans->GetPosition().z + (m_LookPoint.z - m_pTrans->GetPosition().z) * mc_controlPos1Per;
	m_ControlPosition2.x =
		m_pTrans->GetPosition().x + (m_LookPoint.x - m_pTrans->GetPosition().x) * mc_controlPos2Per;
	m_ControlPosition2.y =
		m_pTrans->GetPosition().y + (m_LookPoint.y - m_pTrans->GetPosition().y) * mc_controlPos2Per;
	m_ControlPosition2.z =
		m_pTrans->GetPosition().z + (m_LookPoint.z - m_pTrans->GetPosition().z) * mc_controlPos2Per;

	//--- �T�E���h
	m_pEncounter1SEData = CreateSound("Assets/Sound/SE/A5_05170.wav", false);
	m_pEncounter1SESource = nullptr;
	m_pEncounter2SEData = CreateSound("Assets/Sound/SE/A5_06174.wav", false);
	m_pEncounter2SESource = nullptr;

	// �T�E���h���Đ�
	m_pEncounter1SESource = StartSound(m_pEncounter1SEData);
	m_pEncounter1SESource->SetVolume(0.3f);
}

// �X�V
void CameraEncounter::Update()
{
	// �J�E���g����
	m_tick++;

	// �J�������~�߂�
	if (m_tick <= 30) {

	}
	else 
	// �C�[�Y�C������̃Y�[��
	if (m_tick <= 70) {
		m_pTrans->SetPosition({
			m_startPosition.x + (m_ControlPosition1.x - m_startPosition.x) * (1 - pow(1 - (m_tick / 70), 4)),
			m_startPosition.y + (m_ControlPosition1.y - m_startPosition.y) * (1 - pow(1 - (m_tick / 70), 4)),
			m_startPosition.z + (m_ControlPosition1.z - m_startPosition.z) * (1 - pow(1 - (m_tick / 70), 4)),
			});
	}
	else 
	// �����̃Y�[��
	if (m_tick <= 75) {
		m_pTrans->SetPosition({
			m_ControlPosition1.x + (m_ControlPosition2.x - m_ControlPosition1.x) * (pow(m_tick / 75, 6)),
			m_ControlPosition1.y + (m_ControlPosition2.y - m_ControlPosition1.y) * (pow(m_tick / 75, 6)),
			m_ControlPosition1.z + (m_ControlPosition2.z - m_ControlPosition1.z) * (pow(m_tick / 75, 6))
			});
	}
	else 
	// �J�������~�߂�
	if (m_tick <= 100) {

	}
	else
	// �J��������ɓʂ̓����Řp��
	if (m_tick <= 140) {
		//--- �x�W�G�Ȑ��ł̐���

		// ���O�����v�Z����
		std::float_t rate = (m_tick - 100) / (140 - 100);

		// ���W�̍X�V
		m_pTrans->SetPosition({
			m_startPosition.x							* pow(1 - rate,3)	+ 
			m_ControlPosition1.x * 3 * rate				* pow(1 - rate, 2)	+
			m_ControlPosition2.x * 3 * pow(rate, 2)		* (1 - rate)		+
			m_endPosition.x								* pow(rate, 3),
			m_startPosition.y							* pow(1 - rate,3)	+
			m_ControlPosition1.y * 3 * rate				* pow(1 - rate, 2)	+
			m_ControlPosition2.y * 3 * pow(rate, 2)		* (1 - rate)		+
			m_endPosition.y								* pow(rate, 3),
			m_startPosition.z							* pow(1 - rate,3)	+
			m_ControlPosition1.z * 3 * rate				* pow(1 - rate, 2)	+
			m_ControlPosition2.z * 3 * pow(rate, 2)		* (1 - rate)		+
			m_endPosition.z								* pow(rate, 3)
			});
	}
	else if (m_tick == 141) {

		std::shared_ptr<ObjectBase> pObj;
		std::shared_ptr<ObjectBase> pMainCamera;
		pObj = ObjectManager::CreateObject<CameraObjBase>("BattleCamera");
		pObj->AddComponent<CameraBattle>();
		pMainCamera = ObjectManager::FindObjectWithTag(TagName::MainCamera);
		pObj->GetComponent<CameraBattle>()->SetPosition(
			pMainCamera->GetComponent<Transform>()->GetPosition()
		);
		pObj->GetComponent<CameraBattle>()->SetLookPoint({
			pMainCamera->GetComponent<Transform>()->GetPosition().x - (pMainCamera->GetComponent<Transform>()->GetPosition().x - this->GetLookPoint().x) * 3 / 5,
			pMainCamera->GetComponent<Transform>()->GetPosition().y - (pMainCamera->GetComponent<Transform>()->GetPosition().y - this->GetLookPoint().y) * 3 / 5,
			pMainCamera->GetComponent<Transform>()->GetPosition().z - (pMainCamera->GetComponent<Transform>()->GetPosition().z - this->GetLookPoint().z) * 3 / 5
			});
	//	pObj->GetComponent<CameraBattle>()->SetLookPoint(this->m_LookPoint);
	}
	else {

		// �������폜
		ObjectManager::RemoveObject(GetOwner()->GetThisPtr());
	}


	//--- �v���C���[�����Ɉړ�������
	if (m_tick == 30) {
		std::shared_ptr<Transform> pTrans = ObjectManager::FindObjectWithTag(TagName::Player)->GetComponent<Transform>();
		pTrans->SetPosition({
			pTrans->GetPosition().x + pTrans->GetVectorRight().x * 12,
			pTrans->GetPosition().y + pTrans->GetVectorRight().y * 12,
			pTrans->GetPosition().z + pTrans->GetVectorRight().z * 12
			});

		// �T�E���h���Đ�
		m_pEncounter2SESource = StartSound(m_pEncounter2SEData);
		m_pEncounter2SESource->SetVolume(0.1f);
	}

	//--- �x�W�G�Ȑ��Ŏg�p���鐧��_�̃Z�b�g
	if (m_tick == 90) {
		std::shared_ptr<Transform> pTrans = ObjectManager::FindObjectWithTag(TagName::Player)->GetComponent<Transform>();
		// �I���n�_�̃Z�b�g
		m_endPosition = {
			(pTrans->GetPosition().x + pTrans->GetVectorRight().x * 6),
			(pTrans->GetPosition().y + pTrans->GetVectorRight().y * 6 + 4),
			(pTrans->GetPosition().z + pTrans->GetVectorRight().z * 6)
		};
		// �J�n�n�_�̃Z�b�g
		m_startPosition = m_pTrans->GetPosition();
		// ����_1�̃Z�b�g
		m_ControlPosition1 = {
			(pTrans->GetPosition().x + pTrans->GetVectorRight().x * 2),
			(pTrans->GetPosition().y + pTrans->GetVectorRight().y * 2 + 5),
			(pTrans->GetPosition().z + pTrans->GetVectorRight().z * 2)
		};
		// ����_2�̃Z�b�g
		m_ControlPosition2 = {
			(pTrans->GetPosition().x + pTrans->GetVectorRight().x * 4),
			(pTrans->GetPosition().y + pTrans->GetVectorRight().y * 4 + 6),
			(pTrans->GetPosition().z + pTrans->GetVectorRight().z * 4)
		};
	}
}

void CameraEncounter::SetPosition(const DirectX::XMFLOAT3& _position)
{
	m_startPosition = _position;
	GetOwner()->GetComponent<Transform>()->SetPosition(_position);
}