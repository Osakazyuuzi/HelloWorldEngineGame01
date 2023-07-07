#ifndef ___RONA_ICON_CONTROLLER_H___
#define ___RONA_ICON_CONTROLLER_H___

#include "ComponentBase.h"
#include <memory>
#include "Status.h"

//-------------------
// �R���|�[�l���g
//-------------------
// ����UI�F���i�̃A�C�R��
class RonaIconController : public ComponentBase {
public:
	// �R���X�g���N�^
	RonaIconController() {}
	// �f�X�g���N�^
	~RonaIconController() {}

	// ������
	void Start() override final;

	// �X�V
	void Update() override final;

	constexpr static float mc_InitPos = 200.0f;

private:

	std::shared_ptr<Status> m_pStatus;
};

#endif //!___RONA_ICON_CONTROLLER_H___