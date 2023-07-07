#ifndef ___CAMERA_PLAYER_H___
#define ___CAMERA_PLAYER_H___

#include "Camera.h"

class CameraPlayer : public Camera
{
public:
	// �R���X�g���N�^
	CameraPlayer()
		: m_radius(10.0f)
	{}
	// �f�X�g���N�^
	~CameraPlayer(){}

	void Update() override;

	//--- �Z�b�g�֐�
	void SetRadXZ(float rad) { m_radXZ = rad; }
	void SetRadY(float rad) { m_radY = rad; }

private:
	float m_radXZ, m_radY;		// ��荞�݊p�x
	float m_radius;				// �J�����ƒ����_�̋���
};

#endif //!___CAMERA_PLAYER_H___