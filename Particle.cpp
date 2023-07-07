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

// 描画
void Particle::Draw() {

	m_life--;
	if (m_life <= 0) ObjectManager::RemoveObject(this->GetThisPtr());

	std::shared_ptr<SpriteRenderer> pSprite = GetComponent<SpriteRenderer>();


	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
		GetComponent<Transform>()->GetPosition().x,
		GetComponent<Transform>()->GetPosition().y-2,
		GetComponent<Transform>()->GetPosition().x);

	//--- 頭上にバーを表示
	// ビルボードの作成
	// ビルボードはカメラの回転行列を打ち消す行列を
	// 作成する必要がある。(左に30°回転→右に30°回転
	// 但し行列の回転成分からはどう回転しているか
	// わからない。
	// 中身は分からなくとも、打ち消す行列だけは創れる。
	// 打ち消す行列を"逆行列"という。
	DirectX::XMFLOAT4X4 inv;	// 逆行列(inverse)の格納先
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

	// 転置されている行列なので、一度元に戻す
	DirectX::XMMATRIX matInv =
		DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);
	// 移動成分は打ち消す必要がないので、
	// 0を設定して移動を無視する
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;
	// 逆行列の計算はXMMATRIX型で行う
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