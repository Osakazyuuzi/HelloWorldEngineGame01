#ifndef ___CAMERA_H___
#define ___CAMERA_H___

// ���ӁF���̃w�b�_��Component�ł��B�J�������̂��̂ł͂���܂���B

#include <DirectXMath.h>
#include"ComponentBase.h"

class Camera : public ComponentBase
{
public:
	// �R���X�g���N�^
	Camera()
		: m_LookPoint{0.0f, 0.0f, 0.0f}
		, m_upVector{0.0f, 1.0f, 0.0f}
		, m_fovy(60.0f), m_aspect(16.0f / 9.0f), m_near(0.3f), m_far(1000.0f)
	{}
	// �f�X�g���N�^
	virtual ~Camera(){}

	// �X�V�֐�
	virtual void Update(){}

	//--- �Q�b�g�֐�
	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT3 GetLookPoint() { return m_LookPoint; }

protected:
	//--- �r���[�s��ɕK�v�ȏ��
	// �����_
	DirectX::XMFLOAT3 m_LookPoint;
	// �A�b�v�x�N�g��
	DirectX::XMFLOAT3 m_upVector;

	//--- �v���W�F�N�V�����s��ɕK�v�ȏ��
	float m_fovy, m_aspect, m_near, m_far;
};

#endif //!___CAMERA_H___