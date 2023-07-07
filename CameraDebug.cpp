#include "CameraDebug.h"
#include "WinUtil.h"
#include "Input.h"
#include "Transform.h"
#include "ObjectBase.h"

void CameraDebug::Update()
{
	// Alt�L�[
	if (IsKeyPress(VK_MENU))
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
			// �}�E�X�����
			if (m_CursorPos.y < GetCursorPos().y)
				m_radY -= (m_CursorPos.y - GetCursorPos().y) / 180 * 3.141592f * m_RotateSensitivity;
			// �}�E�X������
			if (m_CursorPos.y > GetCursorPos().y)
				m_radY += (GetCursorPos().y - m_CursorPos.y) / 180 * 3.141592f * m_RotateSensitivity;

			//=========================
			// Y�̉�荞�݂������ۂɁA
			//  �A�b�v�x�N�g���ϊ��̕K�v�����`�F�b�N
			//=========================
			//??????????????????????
		}
		// �}�E�X�̒��{�^��
		else if (IsKeyPress(VK_MBUTTON))
		{
			//=========================
			// Alt�L�[�{�}�E�X���{�^����
			//  �����_�ƃJ�����𓮂���
			//=========================

			// �}�E�X���E��
			if (m_CursorPos.x < GetCursorPos().x) {
				m_LookPoint.x -= cosf(m_radXZ) * (m_CursorPos.x - GetCursorPos().x) * 0.01f;
				m_LookPoint.z -= -sinf(m_radXZ) * (m_CursorPos.x - GetCursorPos().x) * 0.01f;
			}
			// �}�E�X������
			if (m_CursorPos.x > GetCursorPos().x) {
				m_LookPoint.x += cosf(m_radXZ) * (GetCursorPos().x - m_CursorPos.x) * 0.01f;
				m_LookPoint.z += -sinf(m_radXZ) * (GetCursorPos().x - m_CursorPos.x) * 0.01f;
			}
			// �}�E�X�����
			if (m_CursorPos.y < GetCursorPos().y) {
				m_LookPoint.x -= sinf(m_radY) * -sinf(m_radXZ) * (m_CursorPos.y - GetCursorPos().y) * 0.01f;
				m_LookPoint.y += -cosf(m_radY) * (m_CursorPos.y - GetCursorPos().y) * 0.01f;
				m_LookPoint.z -= sinf(m_radY) * -cosf(m_radXZ) * (m_CursorPos.y - GetCursorPos().y) * 0.01f;
			}
			// �}�E�X������
			if (m_CursorPos.y > GetCursorPos().y) {
				m_LookPoint.x -= -sinf(m_radY) * sinf(m_radXZ) * (m_CursorPos.y - GetCursorPos().y) * 0.01f;
				m_LookPoint.y += -cosf(m_radY) * (m_CursorPos.y - GetCursorPos().y) * 0.01f;
				m_LookPoint.z -= -sinf(m_radY) * cosf(m_radXZ) * (m_CursorPos.y - GetCursorPos().y) * 0.01f;
			}
		}
	}

	//=========================
	// �}�E�X�z�C�[����
	//  �J�����𐳖ʂɐi�܂���
	//=========================
	// �z�C�[���̉񂵂������������_�ƃJ�������W�̋����𑀍삷��
	m_radius -= (GetMouseWheel() * m_ZoomSensitivity);
	// �}�E�X�z�C�[��������������
	InitMouseWheel();

	// �p�x�Ƌ����A�����X����J�����̈ʒu���v�Z
	GetOwner()->GetComponent<Transform>()->SetPosition({
	cosf(m_radY) * sinf(m_radXZ) * m_radius + m_LookPoint.x,
	sinf(m_radY) * m_radius + m_LookPoint.y,
	cosf(m_radY) * cosf(m_radXZ) * m_radius + m_LookPoint.z
	});
	// ���݂̃J�[�\�����W�ōX�V
	m_CursorPos = GetCursorPos();
}