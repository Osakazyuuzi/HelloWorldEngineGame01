#ifndef ___RONA_ICON_H___
#define ___RONA_ICON_H___

#include "UI.h"
#include "RonaIconController.h"
#include "Transform.h"

class RonaIcon : public UI
{
public:
	// コンストラクタ
	RonaIcon(std::string name, std::string tag) : UI(name, tag) {
		// コンポーネント追加
		AddComponent<RonaIconController>();
		// 画像をロード
		std::shared_ptr<SpriteRenderer> pSpriteRenderer;
		std::shared_ptr<Transform> pTransform;
		pSpriteRenderer = GetComponent<SpriteRenderer>();
		pTransform = GetComponent<Transform>();

		pSpriteRenderer->LoadTexture("Assets/Texture/RonaIcon.png");
		pSpriteRenderer->SetSize(50, 50);
		SetLayerNum(2);
		pTransform->SetPosition({ -550.0f, 200.0f, 0.0f });
	}
	// デストラクタ
	~RonaIcon() {}
};

#endif //!___RONA_ICON_H___