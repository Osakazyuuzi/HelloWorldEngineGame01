#ifndef ___LOADUI_H___
#define ___LOADUI_H___

#include "UI.h"
#include "Transform.h"
#include "LoadUIController.h"

class LoadUI : public UI
{
public:
	// コンストラクタ
	LoadUI(std::string name, std::string tag) : UI(name, tag)
	{
		std::shared_ptr<SpriteRenderer> pSprite;
		std::shared_ptr<Transform> pTrans;
		pSprite = GetComponent<SpriteRenderer>();
		pTrans = GetComponent<Transform>();
		AddComponent<LoadUIController>();

		pSprite->LoadTexture("Assets/Texture/Text_Fieldout.png");
		pSprite->SetSize(1000, 200);
		SetLayerNum(1);
		pTrans->SetPosition({ 0.0f, 200.0f, 0.0f });
	}
};

#endif //!___LOADUI_H___