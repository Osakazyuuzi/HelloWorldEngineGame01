#include "CameraEncounter.h"
#include "ObjectBase.h"
#include "CameraObjBase.h"
#include "ObjectManager.h"
#include <memory>
#include "CameraBattle.h"

// コンストラクタ
CameraEncounter::CameraEncounter()
	: m_tick(0.0f)
	, m_IsEnd(false)
{

}

// デストラクタ
CameraEncounter::~CameraEncounter()
{

}

// 初期化
void CameraEncounter::Start()
{
	// メインカメラにする
	static_cast<CameraObjBase*>(GetOwner())->ChangeToMainCamera();

	// ポインタを取得
	m_pTrans = GetOwner()->GetComponent<Transform>();
	// 制御点の座標を算出
	m_ControlPosition1.x = 
		m_pTrans->GetPosition().x + (m_LookPoint.x - m_pTrans->GetPosition().x) * mc_controlPos1Per;
	m_ControlPosition1.y =
		m_pTrans->GetPosition().y + (m_LookPoint.y - m_pTrans->GetPosition().y) * mc_controlPos1Per;
	m_ControlPosition1.z =
		m_pTrans->GetPosition().z + (m_LookPoint.z - m_pTrans->GetPosition().z) * mc_controlPos1Per;
	m_ControlPosition2.x =
		m_pTrans->GetPosition().x + (m_LookPoint.x - m_pTrans->GetPosition().x) * mc_controlPos2Per;
	m_ControlPosition2.y =
		m_pTrans->GetPosition().y + (m_LookPoint.y - m_pTrans->GetPosition().y) * mc_controlPos2Per;
	m_ControlPosition2.z =
		m_pTrans->GetPosition().z + (m_LookPoint.z - m_pTrans->GetPosition().z) * mc_controlPos2Per;

	//--- サウンド
	m_pEncounter1SEData = CreateSound("Assets/Sound/SE/A5_05170.wav", false);
	m_pEncounter1SESource = nullptr;
	m_pEncounter2SEData = CreateSound("Assets/Sound/SE/A5_06174.wav", false);
	m_pEncounter2SESource = nullptr;

	// サウンドを再生
	m_pEncounter1SESource = StartSound(m_pEncounter1SEData);
	m_pEncounter1SESource->SetVolume(0.3f);
}

// 更新
void CameraEncounter::Update()
{
	// カウントする
	m_tick++;

	// カメラを止める
	if (m_tick <= 30) {

	}
	else 
	// イーズインありのズーム
	if (m_tick <= 70) {
		m_pTrans->SetPosition({
			m_startPosition.x + (m_ControlPosition1.x - m_startPosition.x) * (1 - pow(1 - (m_tick / 70), 4)),
			m_startPosition.y + (m_ControlPosition1.y - m_startPosition.y) * (1 - pow(1 - (m_tick / 70), 4)),
			m_startPosition.z + (m_ControlPosition1.z - m_startPosition.z) * (1 - pow(1 - (m_tick / 70), 4)),
			});
	}
	else 
	// ただのズーム
	if (m_tick <= 75) {
		m_pTrans->SetPosition({
			m_ControlPosition1.x + (m_ControlPosition2.x - m_ControlPosition1.x) * (pow(m_tick / 75, 6)),
			m_ControlPosition1.y + (m_ControlPosition2.y - m_ControlPosition1.y) * (pow(m_tick / 75, 6)),
			m_ControlPosition1.z + (m_ControlPosition2.z - m_ControlPosition1.z) * (pow(m_tick / 75, 6))
			});
	}
	else 
	// カメラを止める
	if (m_tick <= 100) {

	}
	else
	// カメラを上に凸の動きで湾曲
	if (m_tick <= 140) {
		//--- ベジエ曲線での制御

		// 事前準備計算部分
		std::float_t rate = (m_tick - 100) / (140 - 100);

		// 座標の更新
		m_pTrans->SetPosition({
			m_startPosition.x							* pow(1 - rate,3)	+ 
			m_ControlPosition1.x * 3 * rate				* pow(1 - rate, 2)	+
			m_ControlPosition2.x * 3 * pow(rate, 2)		* (1 - rate)		+
			m_endPosition.x								* pow(rate, 3),
			m_startPosition.y							* pow(1 - rate,3)	+
			m_ControlPosition1.y * 3 * rate				* pow(1 - rate, 2)	+
			m_ControlPosition2.y * 3 * pow(rate, 2)		* (1 - rate)		+
			m_endPosition.y								* pow(rate, 3),
			m_startPosition.z							* pow(1 - rate,3)	+
			m_ControlPosition1.z * 3 * rate				* pow(1 - rate, 2)	+
			m_ControlPosition2.z * 3 * pow(rate, 2)		* (1 - rate)		+
			m_endPosition.z								* pow(rate, 3)
			});
	}
	else if (m_tick == 141) {

		std::shared_ptr<ObjectBase> pObj;
		std::shared_ptr<ObjectBase> pMainCamera;
		pObj = ObjectManager::CreateObject<CameraObjBase>("BattleCamera");
		pObj->AddComponent<CameraBattle>();
		pMainCamera = ObjectManager::FindObjectWithTag(TagName::MainCamera);
		pObj->GetComponent<CameraBattle>()->SetPosition(
			pMainCamera->GetComponent<Transform>()->GetPosition()
		);
		pObj->GetComponent<CameraBattle>()->SetLookPoint({
			pMainCamera->GetComponent<Transform>()->GetPosition().x - (pMainCamera->GetComponent<Transform>()->GetPosition().x - this->GetLookPoint().x) * 3 / 5,
			pMainCamera->GetComponent<Transform>()->GetPosition().y - (pMainCamera->GetComponent<Transform>()->GetPosition().y - this->GetLookPoint().y) * 3 / 5,
			pMainCamera->GetComponent<Transform>()->GetPosition().z - (pMainCamera->GetComponent<Transform>()->GetPosition().z - this->GetLookPoint().z) * 3 / 5
			});
	//	pObj->GetComponent<CameraBattle>()->SetLookPoint(this->m_LookPoint);
	}
	else {

		// 自分を削除
		ObjectManager::RemoveObject(GetOwner()->GetThisPtr());
	}


	//--- プレイヤーを後ろに移動させる
	if (m_tick == 30) {
		std::shared_ptr<Transform> pTrans = ObjectManager::FindObjectWithTag(TagName::Player)->GetComponent<Transform>();
		pTrans->SetPosition({
			pTrans->GetPosition().x + pTrans->GetVectorRight().x * 12,
			pTrans->GetPosition().y + pTrans->GetVectorRight().y * 12,
			pTrans->GetPosition().z + pTrans->GetVectorRight().z * 12
			});

		// サウンドを再生
		m_pEncounter2SESource = StartSound(m_pEncounter2SEData);
		m_pEncounter2SESource->SetVolume(0.1f);
	}

	//--- ベジエ曲線で使用する制御点のセット
	if (m_tick == 90) {
		std::shared_ptr<Transform> pTrans = ObjectManager::FindObjectWithTag(TagName::Player)->GetComponent<Transform>();
		// 終了地点のセット
		m_endPosition = {
			(pTrans->GetPosition().x + pTrans->GetVectorRight().x * 6),
			(pTrans->GetPosition().y + pTrans->GetVectorRight().y * 6 + 4),
			(pTrans->GetPosition().z + pTrans->GetVectorRight().z * 6)
		};
		// 開始地点のセット
		m_startPosition = m_pTrans->GetPosition();
		// 制御点1のセット
		m_ControlPosition1 = {
			(pTrans->GetPosition().x + pTrans->GetVectorRight().x * 2),
			(pTrans->GetPosition().y + pTrans->GetVectorRight().y * 2 + 5),
			(pTrans->GetPosition().z + pTrans->GetVectorRight().z * 2)
		};
		// 制御点2のセット
		m_ControlPosition2 = {
			(pTrans->GetPosition().x + pTrans->GetVectorRight().x * 4),
			(pTrans->GetPosition().y + pTrans->GetVectorRight().y * 4 + 6),
			(pTrans->GetPosition().z + pTrans->GetVectorRight().z * 4)
		};
	}
}

void CameraEncounter::SetPosition(const DirectX::XMFLOAT3& _position)
{
	m_startPosition = _position;
	GetOwner()->GetComponent<Transform>()->SetPosition(_position);
}