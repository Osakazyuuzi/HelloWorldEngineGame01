#include "SceneLose.h"
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
#include "ButtonT.h"

SceneLose::SceneLose()
{
	//--- 変更用ポインタ
	std::shared_ptr<ObjectBase> pObj;
	std::shared_ptr<MeshRenderer> pMeshRenderer;	// 3Dオブジェクト用レンダラー
	std::shared_ptr<SpriteRenderer> pSpriteRenderer;// 2Dオブジェクト用レンダラー
	std::shared_ptr<Transform> pTransform;			// 位置情報
	std::shared_ptr<Rigidbody> pRigidbody;			// 物理挙動
	std::shared_ptr<AABBCollider> pAABBCollider;
	std::shared_ptr<CameraPlayer> pCameraPlayer;

	pObj = ObjectManager::CreateObject<UI>("UI_Tera_Icon");
	pSpriteRenderer = pObj->GetComponent<SpriteRenderer>();
	pTransform = pObj->GetComponent<Transform>();
	pSpriteRenderer->LoadTexture("Assets/Texture/Lose.png");
	pSpriteRenderer->SetSize(300, 200);
	pObj->SetLayerNum(1);
	pTransform->SetPosition({ 0.0f, 0.0f, 0.0f });

	pObj = ObjectManager::CreateObject<UI>("UI_Tera_Icon");
	pSpriteRenderer = pObj->GetComponent<SpriteRenderer>();
	pObj->AddComponent<ButtonT>();
	pTransform = pObj->GetComponent<Transform>();
	pSpriteRenderer->LoadTexture("Assets/Texture/TitleStart.png");
	pSpriteRenderer->SetSize(300, 200);
	pObj->SetLayerNum(1);
	pTransform->SetPosition({ 0.0f, -200.0f, 0.0f });
}

SceneLose::~SceneLose()
{

}
