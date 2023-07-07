#include "Particle.h"
#include "ObjectManager.h"
#include "ObjectBase.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraDebug.h"
#include "CameraPlayer.h"
#include "CameraEncounter.h"
#include "CameraBattle.h"
#include "Status.h"

// �`��
void Particle::Draw() {

	m_life--;
	if (m_life <= 0) ObjectManager::RemoveObject(this->GetThisPtr());

	std::shared_ptr<SpriteRenderer> pSprite = GetComponent<SpriteRenderer>();


	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
		GetComponent<Transform>()->GetPosition().x,
		GetComponent<Transform>()->GetPosition().y-2,
		GetComponent<Transform>()->GetPosition().x);

	//--- ����Ƀo�[��\��
	// �r���{�[�h�̍쐬
	// �r���{�[�h�̓J�����̉�]�s���ł������s���
	// �쐬����K�v������B(����30����]���E��30����]
	// �A���s��̉�]��������͂ǂ���]���Ă��邩
	// �킩��Ȃ��B
	// ���g�͕�����Ȃ��Ƃ��A�ł������s�񂾂��͑n���B
	// �ł������s���"�t�s��"�Ƃ����B
	DirectX::XMFLOAT4X4 inv;	// �t�s��(inverse)�̊i�[��
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 proj;
	if (ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<Camera>()) {
		view = inv = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<Camera>()->GetViewMatrix();
		proj = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<Camera>()->GetProjectionMatrix();
	}
	else if (ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraDebug>()) {
		view = inv = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraDebug>()->GetViewMatrix();
		proj = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraDebug>()->GetProjectionMatrix();
	}
	else if (ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraPlayer>()) {
		view = inv = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraPlayer>()->GetViewMatrix();
		proj = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraPlayer>()->GetProjectionMatrix();
	}
	else if (ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraEncounter>()) {
		view = inv = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraEncounter>()->GetViewMatrix();
		proj = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraEncounter>()->GetProjectionMatrix();
	}
	else if (ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraBattle>()) {
		view = inv = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraBattle>()->GetViewMatrix();
		proj = ObjectManager::FindObjectWithTag(TagName::MainCamera)->GetComponent<CameraBattle>()->GetProjectionMatrix();
	}

	// �]�u����Ă���s��Ȃ̂ŁA��x���ɖ߂�
	DirectX::XMMATRIX matInv =
		DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);
	// �ړ������͑ł������K�v���Ȃ��̂ŁA
	// 0��ݒ肵�Ĉړ��𖳎�����
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;
	// �t�s��̌v�Z��XMMATRIX�^�ōs��
	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);

	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld, DirectX::XMMatrixTranspose(matInv * T));
	pSprite->SetWorld(fWorld);
	pSprite->SetView(view);
	pSprite->SetProj(proj);


	SetLayerNum(999);
	pSprite->SetColor({ 1.0f, 1.0f, 1.0f, 0.3f });
	pSprite->Draw();
}