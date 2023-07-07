#include "Camera.h"
#include "ObjectBase.h"
#include "Transform.h"

// �r���[�s��
DirectX::XMFLOAT4X4 Camera::GetViewMatrix() {
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	// �r���[�s����쐬
	view = DirectX::XMMatrixLookAtLH(
		// �ʒu
		DirectX::XMVectorSet(
			GetOwner()->GetComponent<Transform>()->GetPosition().x,
			GetOwner()->GetComponent<Transform>()->GetPosition().y,
			GetOwner()->GetComponent<Transform>()->GetPosition().z, 0),
		// �����_
		DirectX::XMVectorSet(m_LookPoint.x, m_LookPoint.y, m_LookPoint.z, 0),
		// �A�b�v�x�N�g��
		DirectX::XMVectorSet(m_upVector.x, m_upVector.y, m_upVector.z, 0));
	// �]�u����
	view = DirectX::XMMatrixTranspose(view);
	// XMFLOAT4x4�ɕϊ�
	DirectX::XMStoreFloat4x4(&mat, view);
	// �]�u�ς݂̃r���[�s���Ԃ�
	return mat;
}

// �v���W�F�N�V�����s��
DirectX::XMFLOAT4X4 Camera::GetProjectionMatrix() {
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	// �v���W�F�N�V�����s����쐬
	proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(m_fovy), m_aspect, m_near, m_far);
	// �]�u����
	proj = DirectX::XMMatrixTranspose(proj);
	// XMFLOAT4x4�ɕϊ�
	DirectX::XMStoreFloat4x4(&mat, proj);
	// �]�u�ς݂̃v���W�F�N�V�����s���Ԃ�
	return mat;
}