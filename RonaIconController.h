#ifndef ___RONA_ICON_CONTROLLER_H___
#define ___RONA_ICON_CONTROLLER_H___

#include "ComponentBase.h"
#include <memory>
#include "Status.h"

//-------------------
// コンポーネント
//-------------------
// 所属UI：ロナのアイコン
class RonaIconController : public ComponentBase {
public:
	// コンストラクタ
	RonaIconController() {}
	// デストラクタ
	~RonaIconController() {}

	// 初期化
	void Start() override final;

	// 更新
	void Update() override final;

	constexpr static float mc_InitPos = 200.0f;

private:

	std::shared_ptr<Status> m_pStatus;
};

#endif //!___RONA_ICON_CONTROLLER_H___