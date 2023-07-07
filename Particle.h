#ifndef ___PARTICLE_H___
#define ___PARTICLE_H___

#include "UI.h"
#include "Transform.h"
#include "Rigidbody.h"

class Particle : public UI
{
public:
	// �R���X�g���N�^
	Particle(std::string name, std::string tag) : UI(name, tag) {
		// �R���|�[�l���g�ǉ�
		AddComponent<Rigidbody>();
		// �摜�����[�h
		std::shared_ptr<SpriteRenderer> pSpriteRenderer;
		std::shared_ptr<Transform> pTransform;
		pSpriteRenderer = GetComponent<SpriteRenderer>();
		pTransform = GetComponent<Transform>();

		pSpriteRenderer->LoadTexture("Assets/Texture/WHITE.png");
		pSpriteRenderer->SetSize(1, 1);
		SetLayerNum(999);
		pTransform->SetPosition({ 0.0f, 2.3f, 0.0f });

		m_life = 30.0f;
	}
	// �f�X�g���N�^
	~Particle() {}

	// �`��
	void Draw() override final;

private:
	float m_life;
};

#endif