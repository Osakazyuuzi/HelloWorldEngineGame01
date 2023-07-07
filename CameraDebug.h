#ifndef ___CAMERADEBUG_H___
#define ___CAMERADEBUG_H___

#include "Camera.h"

class CameraDebug : public Camera
{
public:
	// �R���X�g���N�^
	CameraDebug()
		: m_CursorPos({ 0.0f, 0.0f })
		, m_ZoomSensitivity(6.0f)
		, m_RotateSensitivity(0.3f)
		, m_radXZ(0.0f), m_radY(0.0f), m_radius(10.0f)
	{}
	// �f�X�g���N�^
	~CameraDebug(){}

	void Update() override;

private:
	// ��ʑ���p�J�[�\�����W
	DirectX::XMFLOAT2 m_CursorPos;
	float m_ZoomSensitivity;	// �Y�[�����x
	float m_RotateSensitivity;	// ��]���x
	float m_radXZ, m_radY;		// ��荞�݊p�x
	float m_radius;				// �J�����ƒ����_�̋���
};

#endif //!___CAMERADEBUG_H___