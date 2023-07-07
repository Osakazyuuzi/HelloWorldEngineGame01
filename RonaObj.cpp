#include "RonaObj.h"
#include "ObjectBase.h"
#include "Object3D.h"
#include "ObjectManager.h"
#include <memory>
#include "Transform.h"
#include "MeshRenderer.h"
#include "AABBCollider.h"
#include "Rigidbody.h"

#include "RonaController.h"
#include "RonaAnimator.h"
#include "Status.h"

// コンストラクタ
RonaObj::RonaObj()
{
	//--- 変更用ポインタ
	std::shared_ptr<ObjectBase> pChildObj;		// 子オブジェクト用
	std::shared_ptr<ObjectBase> pParent1Obj;	// 深さ１のオブジェクト用
	std::shared_ptr<ObjectBase> pParent2Obj;	// 深さ２のオブジェクト用	
	std::shared_ptr<ObjectBase> pParent3Obj;	// 深さ３のオブジェクト用
	std::shared_ptr<Transform> pTransform;		// Transform
	std::shared_ptr<AABBCollider> pAABBCollider;// AABBCollider
	std::shared_ptr<RonaAnimator> pAnim;		// Animation

	/*-------------------------------------
	 ●キャラクターオブジェクトの親子関係
	 ベース（深さ３）
	   - 体のオブジェクト（深さ２）
		 - 頭のジョイント（深さ１）
		   - 頭のオブジェクト（子）
		   - 装飾品（子）　　　　　　　// 未実装
		 - 右手のジョイント（深さ１）
		 　- 右手のオブジェクト（子）
		 - 左手のジョイント（深さ１）
		 　- 左手のオブジェクト（子）
		 - 右足のジョイント（深さ１）
		 　- 右足のオブジェクト（子）
		 - 左足のジョイント（深さ１）
		 　- 左足のオブジェクト（子）
	 -------------------------------------*/

	 //------------------------------------
	 //--- キャラクターのベースを作成
	pParent3Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona", TagName::Enemy);
	// 操作用コンポーネントを追加
	pParent3Obj->AddComponent<RonaController>();
	// ステータスを追加、初期ステータスを登録
	pParent3Obj->AddComponent<Status>()->SetInitStatus(
		Status::CharacterType::Enemy,
		mc_nInitLevel,
		mc_nInitExperienceMax,
		mc_nInitAttack,
		mc_nInitDefense,
		mc_nInitSpeed,
		mc_nInitMpMax,
		mc_nInitHpMax);
	// プレイヤーアニメーションを追加、ポインタの取得
	pAnim = pParent3Obj->AddComponent<RonaAnimator>();
	// Rigidbodyを追加
	pParent3Obj->AddComponent<Rigidbody>();
	// AABBColliderを追加し、ポインタを取得
	pAABBCollider = pParent3Obj->AddComponent<AABBCollider>();
	// 当たり判定のサイズを設定
	pAABBCollider->SetLen({ mc_sizeX, mc_sizeY, mc_sizeZ });
	// 座標を設定
	pParent3Obj->GetComponent<Transform>()->SetPosition({ 2.0f, 0.0f, 0.0f });

	//------------------------------------
	//--- 体のオブジェクトを作成
	pParent2Obj = ObjectManager::CreateObject<Object3D>("Object_Tera_Rona");
	// モデルの読み込み
	pParent2Obj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Body_WHITE.fbx", 0.7f);
	// Transformのポインタを取得
	pTransform = pParent2Obj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f , 0.0f, 0.0f });
	// 親オブジェクトをセットする
	pParent2Obj->SetParent(pParent3Obj);
	// 子オブジェクトの設定にする
	pParent2Obj->GetComponent<Transform>()->IsRoot(false);
	// 体の色を黒色にする
	pParent2Obj->GetComponent<MeshRenderer>()->SetColor({ 0.2f, 0.2f, 0.2f });
	// ジョイントをセットする
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_BODY, pParent2Obj);

	//------------------------------------
	//--- 頭のジョイントを作成
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Head_Joint");
	// Transformのポインタを取得
	pTransform = pParent1Obj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f , 0.5f, 0.0f });
	// 親オブジェクトをセットする
	pParent1Obj->SetParent(pParent2Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// ジョイントをセットする
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_HEAD, pParent1Obj);

	//------------------------------------
	//--- 頭のオブジェクトを作成
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Head");
	// モデルの読み込み
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Head_WHITE.fbx", 1.0f);
	// Transformのポインタを取得
	pTransform = pChildObj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f ,0.5f, 0.0f });
	// 親オブジェクトをセットする
	pChildObj->SetParent(pParent1Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// 体の色を黒色にする
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });

	//------------------------------------
	//--- 右手のジョイントを作成
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Right_Hand_Joint");
	// Transformのポインタを取得
	pTransform = pParent1Obj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f , 0.2f, 0.4f });
	// 親オブジェクトをセットする
	pParent1Obj->SetParent(pParent2Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// ジョイントをセットする
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_RIGHT_HAND, pParent1Obj);

	//------------------------------------
	//--- 右手のオブジェクトを作成
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Right_Hand");
	// モデルの読み込み
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Hand_WHITE.fbx", 0.2f);
	// Transformのポインタを取得
	pTransform = pChildObj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f, -0.3f, 0.2f });
	// 親オブジェクトをセットする
	pChildObj->SetParent(pParent1Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// 体の色を黒色にする
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });

	//------------------------------------
	//--- 左手のジョイントを作成
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Left_Hand_Joint");
	// Transformのポインタを取得
	pTransform = pParent1Obj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f , 0.2f, -0.4f });
	// 親オブジェクトをセットする
	pParent1Obj->SetParent(pParent2Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// ジョイントをセットする
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_LEFT_HAND, pParent1Obj);

	//------------------------------------
	//--- 左手のオブジェクトを作成
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Left_Hand");
	// モデルの読み込み
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Hand_WHITE.fbx", 0.2f);
	// Transformのポインタを取得
	pTransform = pChildObj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f, -0.3f, -0.2f });
	// 親オブジェクトをセットする
	pChildObj->SetParent(pParent1Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// 体の色を黒色にする
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });

	//------------------------------------
	//--- 右足のジョイントを作成
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Right_Leg_Joint");
	// Transformのポインタを取得
	pTransform = pParent1Obj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f , -0.2f, 0.3f });
	// 親オブジェクトをセットする
	pParent1Obj->SetParent(pParent2Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// ジョイントをセットする
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_RIGHT_LEG, pParent1Obj);

	//------------------------------------
	//--- 右足のオブジェクトを作成
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Right_Leg");
	// モデルの読み込み
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Leg_WHITE.fbx", 0.2f);
	// Transformのポインタを取得
	pTransform = pChildObj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f , -0.5f, 0.0f });
	// 親オブジェクトをセットする
	pChildObj->SetParent(pParent1Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// 体の色を黒色にする
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });

	//------------------------------------
	//--- 左足のジョイントを作成
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Left_Leg_Joint");
	// Transformのポインタを取得
	pTransform = pParent1Obj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f , -0.2f, -0.3f });
	// 親オブジェクトをセットする
	pParent1Obj->SetParent(pParent2Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// ジョイントをセットする
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_LEFT_LEG, pParent1Obj);

	//------------------------------------
	//--- 左足のオブジェクトを作成
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Left_Leg");
	// モデルの読み込み
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Leg_WHITE.fbx", 0.2f);
	// Transformのポインタを取得
	pTransform = pChildObj->GetComponent<Transform>();
	// 相対位置をセットする
	pTransform->SetJointPos({ 0.0f , -0.5f, 0.0f });
	// 親オブジェクトをセットする
	pChildObj->SetParent(pParent1Obj);
	// 子オブジェクトの設定にする
	pTransform->IsRoot(false);
	// 体の色を黒色にする
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });
}

// デストラクタ
RonaObj::~RonaObj()
{

}