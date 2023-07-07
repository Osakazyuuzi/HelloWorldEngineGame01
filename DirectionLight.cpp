#include "DirectionLight.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "Transform.h"

// �R���X�g���N�^
DirectionLight::DirectionLight()
{
}

// �f�X�g���N�^
DirectionLight::~DirectionLight()
{
	if (m_pLightBuf)
		delete m_pLightBuf;
}
void DirectionLight::Start()
{
	//--- ������
	m_pLightBuf = new ConstantBuffer();
	m_pLightBuf->Create(sizeof(Info));

	// �f�B���N�V�������C�g�̌������x�N�g���ɕϊ�
	m_Info.m_Direction = DirectX::XMFLOAT3(1.0f, 1.0f, 0.3f);
	DirectX::XMStoreFloat3(&m_Info.m_Direction, 
		DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&m_Info.m_Direction)));

	//--- ���C�g�r���[�s����v�Z
	DirectX::XMMATRIX view;
	// �r���[�s����쐬
	view = DirectX::XMMatrixLookAtLH(
		// �ʒu
		DirectX::XMVectorSet(
			-m_Info.m_Direction.x * 1000,
			-m_Info.m_Direction.y * 1000,
			-m_Info.m_Direction.z * 1000,
			0.0f),
		// �����_
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		// �A�b�v�x�N�g��
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	// �]�u����
	view = DirectX::XMMatrixTranspose(view);
	// XMFLOAT4x4�ɕϊ�
	DirectX::XMStoreFloat4x4(&m_Info.m_matView, view);

	//--- ���C�g���e�s����v�Z
//	DirectX::XMFLOAT4X4 fProj;
//	DirectX::XMStoreFloat4x4(&fProj,
//		DirectX::XMMatrixTranspose(
//			DirectX::XMMatrixOrthographicOffCenterLH(
//				-640.0f,	// ��ʍ��[�̍��W
//				640.0f,		// ��ʉE�[�̍��W
//				-360.0f,	// ��ʉ��[�̍��W
//				360.0f,		// ��ʏ�[�̍��W
//				0.3f,		// Z�l�Ŏʂ��͈͂̍ŏ��l
//				1000.0f		// Z�l�Ŏʂ��͈͂̍ő�l
//			)
//		));
//	m_Info.m_matProj = fProj;

	DirectX::XMMATRIX proj;
	// �v���W�F�N�V�����s����쐬
	proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(60.0f), 16.0f / 9.0f, 0.3f, 1000.0f);
	// �]�u����
	proj = DirectX::XMMatrixTranspose(proj);
	// XMFLOAT4x4�ɕϊ�
	DirectX::XMStoreFloat4x4(&m_Info.m_matProj, proj);
}

void DirectionLight::SetLight()
{
	//���C�g�̏��������ݒ��_�V�F�[�_�ɑ���
	m_pLightBuf->Write(&m_Info);
	m_pLightBuf->BindVS(1);
}