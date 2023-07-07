#include "CameraBattle.h"
#include "ObjectBase.h"
#include "CameraObjBase.h"
#include "ObjectManager.h"
#include "Input.h"
#include "WinUtil.h"
#include "BattleManager.h"
#include "Define.h"

// �R���X�g���N�^
CameraBattle::CameraBattle()
	: m_CursorPos({ 0.0f, 0.0f })
	, m_RotateSensitivity(0.3f)
	, m_radXZ(0.0f), m_radY(0.0f), m_radius(10.0f)
{

}

// �f�X�g���N�^
CameraBattle::~CameraBattle()
{
	m_pBattleBGMSource->SetVolume(0.0f);
	m_pBattleBGMSource->Stop();
	nhs::SAFE_DELETE(m_pBattleBGMData);
	nhs::SAFE_DELETE(m_pBattleBGMSource);
}

// ������
void CameraBattle::Start()
{
	// ���C���J�����ɂ���
	static_cast<CameraObjBase*>(GetOwner())->ChangeToMainCamera();

	// �o�g���Ǘ��N���X��ǉ�
	GetOwner()->AddComponent<BattleManager>();

	// �|�C���^���擾
	m_pTrans = GetOwner()->GetComponent<Transform>();

	//--- �T�E���h
	m_pBattleBGMData = CreateSound("Assets/Sound/SE/A5_06198.wav", true);
	m_pBattleBGMSource = nullptr;

	// �T�E���h���Đ�
	m_pBattleBGMSource = StartSound(m_pBattleBGMData);
	m_pBattleBGMSource->SetVolume(0.2f);

	// �������v��
	m_radius = ::sqrt(
		::pow(::abs(m_pTrans->GetPosition().x - m_LookPoint.x), 2) +
		::pow(::abs(m_pTrans->GetPosition().y - m_LookPoint.y), 2) +
		::pow(::abs(m_pTrans->GetPosition().z - m_LookPoint.z), 2)
	);

	//--- �p�x���v��
	// Y�p�x
	m_radY = 2.922922f;	// �G���J�E���g�J�����̏I���n�_�̊p�x
	
	// XZ�p�x
	// ���C���J�����̍��W�ƒ����_���擾����
	DirectX::XMFLOAT3 camPos = this->m_pTrans->GetPosition();
	DirectX::XMFLOAT3 camLook = this->m_LookPoint;
	// XY���ł̓񎟌��Ƀx�N�g������������
	camPos.y = 0.0f;
	camLook.y = 0.0f;
	// XMVECTOR�ɕϊ�
	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);
	DirectX::XMVECTOR vCamLook = DirectX::XMLoadFloat3(&camLook);
	// �����_������W�֌����x�N�g�����Z�o(���)
	DirectX::XMVECTOR vBack;
	vBack = DirectX::XMVectorSubtract(vCamPos, vCamLook);
	vBack = DirectX::XMVector3Normalize(vBack);
	float radXZ = 0.0f;
	// X�����ւ̃x�N�g��
	DirectX::XMFLOAT3 zVector = { 0.0f, 0.0f, -1.0f };
	// ���ςƃx�N�g���̒������g����cos�Ƃ����߂�
	DirectX::XMStoreFloat(&radXZ, DirectX::XMVector3Dot(DirectX::XMVector3Normalize(vBack), DirectX::XMLoadFloat3(&zVector)));
	// ���ς���p�x�����߂�
	radXZ = ::acos(radXZ);
	// ���W�A���p���炨�Ȃ��݂̊p�x�ɕύX
	radXZ = DirectX::XMConvertToDegrees(radXZ);
	// ��]���E��]������]���𔻕ʂ��邽�߂ɁA�O�ςŋ��߂�
	// ���߂��O�ς�Y�������v���X�������獶���B
	// ���߂��O�ς�Y�������}�C�i�X��������E���B
	DirectX::XMFLOAT3 rotateDirection;
	DirectX::XMStoreFloat3(&rotateDirection, DirectX::XMVector3Cross(DirectX::XMVector3Normalize(vBack), DirectX::XMLoadFloat3(&zVector)));
	if (rotateDirection.y > 0) radXZ = 180.0f + (180.0f - radXZ);
	m_radXZ = radXZ / 180 * 3.141592f;
}

// �X�V
void CameraBattle::Update()
{
	// �}�E�X�̍��{�^��
	if (IsKeyPress(VK_LBUTTON))
	{
		//=========================
		// Alt�L�[�{�}�E�X���{�^����
		//  �����_�𒆐S�ɉ�]����
		//=========================
		// �}�E�X���E��
		if (m_CursorPos.x < GetCursorPos().x)
			m_radXZ -= (m_CursorPos.x - GetCursorPos().x) / 180 * 3.141592f * m_RotateSensitivity;
		// �}�E�X������
		if (m_CursorPos.x > GetCursorPos().x)
			m_radXZ += (GetCursorPos().x - m_CursorPos.x) / 180 * 3.141592f * m_RotateSensitivity;
	}

	// �p�x�Ƌ����A�����_����J�����̈ʒu���v�Z
	GetOwner()->GetComponent<Transform>()->SetPosition({
	cosf(m_radY) * sinf(m_radXZ) * m_radius + m_LookPoint.x,
	sinf(m_radY) * m_radius + m_LookPoint.y,
	cosf(m_radY) * cosf(m_radXZ) * m_radius + m_LookPoint.z
		});
	// ���݂̃J�[�\�����W�ōX�V
	m_CursorPos = GetCursorPos();
}

void CameraBattle::SetPosition(const DirectX::XMFLOAT3& _position)
{
	GetOwner()->GetComponent<Transform>()->SetPosition(_position);
}