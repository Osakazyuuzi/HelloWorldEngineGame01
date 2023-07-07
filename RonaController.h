#ifndef ___RONA_CONTROLLER_H___
#define ___RONA_CONTROLLER_H___

#include "ComponentBase.h"
#include <memory>
#include <DirectXMath.h>
#include "ObjectBase.h"
#include "Sound.h"
#include "RonaAnimator.h"
#include "Status.h"

//-------------------
// �R���|�[�l���g
//-------------------
// �����L�����N�^�[�F���i
class RonaController : public ComponentBase {
public:
	// �R���X�g���N�^
	RonaController();
	// �f�X�g���N�^
	~RonaController();
	// ������
	void Start() override final;
	// �X�V
	void Update() override final;
	// �����蔻��
	void OnCollisionEnter(ObjectBase* _pObject) override final;
	void OnCollisionStay(ObjectBase* _pObject) override final;

private:
	// �R���|�[�l���g�̃|�C���^
	std::shared_ptr<Status> m_pStatus;
	std::shared_ptr<RonaAnimator> m_pAnimtor;

	float m_TargetRotY;
	float m_lateRotY;	// �x��Ă��Ă���Y�p�x

	//--- �T�E���h
	XAUDIO2_BUFFER* m_pWalkSEData;
	IXAudio2SourceVoice* m_pWalkSESource;

private:
	// �����I�u�W�F�N�g�̃|�C���^
	std::shared_ptr<ObjectBase> m_pOwner;
};

#endif //!___TERA_CONTROLLER_H___