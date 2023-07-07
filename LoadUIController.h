#ifndef ___LOADUI_CONTROLLER_H___
#define ___LOADUI_CONTROLLER_H___

#include "ComponentBase.h"

class LoadUIController : public ComponentBase
{
public:
	// コンストラクタ
	LoadUIController() {}
	// デストラクタ
	~LoadUIController() {}

	// 更新
	void Update() override final;
};

#endif //!___LOADUI_CONTROLLER_H___