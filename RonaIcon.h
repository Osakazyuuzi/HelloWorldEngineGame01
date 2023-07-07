#ifndef ___RONA_ICON_H___
#define ___RONA_ICON_H___

#include "UI.h"
#include "RonaIconController.h"
#include "Transform.h"

class RonaIcon : public UI
{
public:
	// �R���X�g���N�^
	RonaIcon(std::string name, std::string tag) : UI(name, tag) {
		// �R���|�[�l���g�ǉ�
		AddComponent<RonaIconController>();
		// �摜�����[�h
		std::shared_ptr<SpriteRenderer> pSpriteRenderer;
		std::shared_ptr<Transform> pTransform;
		pSpriteRenderer = GetComponent<SpriteRenderer>();
		pTransform = GetComponent<Transform>();

		pSpriteRenderer->LoadTexture("Assets/Texture/RonaIcon.png");
		pSpriteRenderer->SetSize(50, 50);
		SetLayerNum(2);
		pTransform->SetPosition({ -550.0f, 200.0f, 0.0f });
	}
	// �f�X�g���N�^
	~RonaIcon() {}
};

#endif //!___RONA_ICON_H___