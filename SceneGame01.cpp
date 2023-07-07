#include "SceneGame01.h"
#include "CameraObjBase.h"
#include "MeshRenderer.h"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "ObjectManager.h"
#include "Object3D.h"
#include "Cube.h"


#include "Transform.h"
#include "CameraObjPlayer.h"

#include "TeraObj.h"
#include "RonaObj.h"

#include "DirectionLightObj.h"

#include "AABBCollider.h"

#include "Stage01Obj.h"

#include "ActionGage.h"
#include "TeraIcon.h"
#include "RonaIcon.h"

#include "RonaHPBarObj.h"

#include "Polyline.h"

SceneGame01::SceneGame01()
{
	//--- 変更用ポインタ
	std::shared_ptr<ObjectBase> pObj;
	std::shared_ptr<MeshRenderer> pMeshRenderer;	// 3Dオブジェクト用レンダラー
	std::shared_ptr<SpriteRenderer> pSpriteRenderer;// 2Dオブジェクト用レンダラー
	std::shared_ptr<Transform> pTransform;			// 位置情報
	std::shared_ptr<Rigidbody> pRigidbody;			// 物理挙動
	std::shared_ptr<AABBCollider> pAABBCollider;
	std::shared_ptr<CameraPlayer> pCameraPlayer;

	//--- オブジェクト作成
	//   型　：CameraPlayer
	//  名前 ：CameraPlayer
	// タグ名：CameraPlayer
	pObj = ObjectManager::CreateObject<CameraObjPlayer>("CameraPlayer", TagName::MainCamera);
	//	pObj->AddComponent<CameraDebug>();
		// CameraPlayerのポインタを取得する
	pCameraPlayer = pObj->GetComponent<CameraPlayer>();
	
	// 角度を設定する
	pCameraPlayer->SetRadY(DirectX::XMConvertToRadians(10.0f));
	pCameraPlayer->SetRadXZ(DirectX::XMConvertToRadians(90.0f));

	//--- ディレクションライトを作成
	pObj = ObjectManager::CreateObject<DirectionLightObj>("MainDirectionLight", TagName::MainLight);

	//--- プレイヤーを作成
	// テラ
	std::shared_ptr<TeraObj> pTera = std::make_shared<TeraObj>();
	// ロナ
	std::shared_ptr<RonaObj> pRona = std::make_shared<RonaObj>();

	//--- ステージを作成
	std::shared_ptr<Stage01Obj> pStage = std::make_shared<Stage01Obj>();
}

SceneGame01::~SceneGame01()
{

}