#ifndef ___CAMERA_BATTLE_H___
#define ___CAMERA_BATTLE_H___

#include "Camera.h"
#include <DirectXMath.h>
#include <memory>
#include "Transform.h"
#include "Sound.h"
#include <cstdint>

class CameraBattle : public Camera
{
public:
	// �R���X�g���N�^
	CameraBattle();
	// �f�X�g���N�^
	~CameraBattle();

	// ������
	void Start() override final;
	// �X�V
	void Update() override final;

	//--- �Z�b�g�֐�
	void SetPosition(const DirectX::XMFLOAT3& _position);
	void SetLookPoint(const DirectX::XMFLOAT3& _lookPoint) {
		m_LookPoint = _lookPoint;
	}

private:

	std::shared_ptr<Transform> m_pTrans;

	//--- �T�E���h
	XAUDIO2_BUFFER* m_pBattleBGMData;
	IXAudio2SourceVoice* m_pBattleBGMSource;

	// ��ʑ���p�J�[�\�����W
	DirectX::XMFLOAT2 m_CursorPos;
	std::float_t m_RotateSensitivity;	// ��]���x
	std::float_t m_radXZ, m_radY;		// ��荞�݊p�x
	std::float_t m_radius;				// �J�����ƒ����_�̋���
};

#endif //!___CAMERA_BATTLE_H___