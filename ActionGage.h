#ifndef ___ACTIONGAGE_H___
#define ___ACTIONGAGE_H___

#include "UI.h"
#include "SpriteRenderer.h"

class ActionGage : public UI
{
public:
	// �R���X�g���N�^
	ActionGage(std::string name, std::string tag) : UI(name, tag) {
		// �摜�����[�h
		std::shared_ptr<SpriteRenderer> pSpriteRenderer;
		std::shared_ptr<Transform> pTransform;
		pSpriteRenderer = GetComponent<SpriteRenderer>();
		pTransform = GetComponent<Transform>();

		pSpriteRenderer->LoadTexture("Assets/Texture/Square.png");
		pSpriteRenderer->SetSize(10, 300);
		SetLayerNum(1);
		pTransform->SetPosition({ -550.0f, 50.0f, 0.0f });
	}
	// �f�X�g���N�^
	~ActionGage() {}

	// �`��
	void Draw() override final {
		this->GetComponent<SpriteRenderer>()->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		this->GetComponent<SpriteRenderer>()->Draw();
	}
};


#endif //!___ACTIONGAGE_H___