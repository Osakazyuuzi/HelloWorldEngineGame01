#ifndef ___RONA_HPBAR_H___
#define ___RONA_HPBAR_H___

#include "UI.h"
#include "Transform.h"

class RonaHPBar : public UI
{
public:
	// �R���X�g���N�^
	RonaHPBar(std::string name, std::string tag) : UI(name, tag) {
		// �R���|�[�l���g�ǉ�
	//	AddComponent<RonaIconController>();
		// �摜�����[�h
		std::shared_ptr<SpriteRenderer> pSpriteRenderer;
		std::shared_ptr<Transform> pTransform;
		pSpriteRenderer = GetComponent<SpriteRenderer>();
		pTransform = GetComponent<Transform>();

		pSpriteRenderer->LoadTexture("Assets/Texture/WHITE.png");
		pSpriteRenderer->SetSize(3, 0.3);
		SetLayerNum(999);
		pTransform->SetPosition({ 0.0f, 2.3f, 0.0f });
	}
	// �f�X�g���N�^
	~RonaHPBar() {}


	// �`��
	void Draw() override final;
};

#endif //!___RONA_ICON_H___