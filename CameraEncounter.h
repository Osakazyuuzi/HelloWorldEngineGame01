#ifndef ___CAMERA_ENCOUNTER_H___
#define ___CAMERA_ENCOUNTER_H___

#include "Camera.h"
#include <cstdint>
#include <DirectXMath.h>
#include <memory>
#include "Transform.h"
#include "Sound.h"

class CameraEncounter : public Camera
{
public:
	// �R���X�g���N�^
	CameraEncounter();
	// �f�X�g���N�^
	~CameraEncounter();

	// ������
	void Start() override final;
	// �X�V
	void Update() override final;

	//--- �Z�b�g�֐�
	void SetPosition(const DirectX::XMFLOAT3& _position);
	void SetLookPoint(const DirectX::XMFLOAT3& _lookPoint) {
		m_LookPoint = _lookPoint;
	}

	//--- �Q�b�g�֐�
	const bool& IsEnd() noexcept { return m_IsEnd; }

	constexpr static std::float_t mc_controlPos1Per = 0.4f;
	constexpr static std::float_t mc_controlPos2Per = 0.5f;

private:
	DirectX::XMFLOAT3 m_startPosition;
	DirectX::XMFLOAT3 m_ControlPosition1;
	DirectX::XMFLOAT3 m_ControlPosition2;
	DirectX::XMFLOAT3 m_endPosition;

	std::shared_ptr<Transform> m_pTrans;

	std::float_t m_tick;
	bool m_IsEnd;

	//--- �T�E���h
	XAUDIO2_BUFFER* m_pEncounter1SEData;
	IXAudio2SourceVoice* m_pEncounter1SESource;
	XAUDIO2_BUFFER* m_pEncounter2SEData;
	IXAudio2SourceVoice* m_pEncounter2SESource;
};

#endif //!___CAMERA_EVENT_H___