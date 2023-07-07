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
	//--- �ύX�p�|�C���^
	std::shared_ptr<ObjectBase> pObj;
	std::shared_ptr<MeshRenderer> pMeshRenderer;	// 3D�I�u�W�F�N�g�p�����_���[
	std::shared_ptr<SpriteRenderer> pSpriteRenderer;// 2D�I�u�W�F�N�g�p�����_���[
	std::shared_ptr<Transform> pTransform;			// �ʒu���
	std::shared_ptr<Rigidbody> pRigidbody;			// ��������
	std::shared_ptr<AABBCollider> pAABBCollider;
	std::shared_ptr<CameraPlayer> pCameraPlayer;

	//--- �I�u�W�F�N�g�쐬
	//   �^�@�FCameraPlayer
	//  ���O �FCameraPlayer
	// �^�O���FCameraPlayer
	pObj = ObjectManager::CreateObject<CameraObjPlayer>("CameraPlayer", TagName::MainCamera);
	//	pObj->AddComponent<CameraDebug>();
		// CameraPlayer�̃|�C���^���擾����
	pCameraPlayer = pObj->GetComponent<CameraPlayer>();
	
	// �p�x��ݒ肷��
	pCameraPlayer->SetRadY(DirectX::XMConvertToRadians(10.0f));
	pCameraPlayer->SetRadXZ(DirectX::XMConvertToRadians(90.0f));

	//--- �f�B���N�V�������C�g���쐬
	pObj = ObjectManager::CreateObject<DirectionLightObj>("MainDirectionLight", TagName::MainLight);

	//--- �v���C���[���쐬
	// �e��
	std::shared_ptr<TeraObj> pTera = std::make_shared<TeraObj>();
	// ���i
	std::shared_ptr<RonaObj> pRona = std::make_shared<RonaObj>();

	//--- �X�e�[�W���쐬
	std::shared_ptr<Stage01Obj> pStage = std::make_shared<Stage01Obj>();
}

SceneGame01::~SceneGame01()
{

}