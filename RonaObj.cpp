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

// �R���X�g���N�^
RonaObj::RonaObj()
{
	//--- �ύX�p�|�C���^
	std::shared_ptr<ObjectBase> pChildObj;		// �q�I�u�W�F�N�g�p
	std::shared_ptr<ObjectBase> pParent1Obj;	// �[���P�̃I�u�W�F�N�g�p
	std::shared_ptr<ObjectBase> pParent2Obj;	// �[���Q�̃I�u�W�F�N�g�p	
	std::shared_ptr<ObjectBase> pParent3Obj;	// �[���R�̃I�u�W�F�N�g�p
	std::shared_ptr<Transform> pTransform;		// Transform
	std::shared_ptr<AABBCollider> pAABBCollider;// AABBCollider
	std::shared_ptr<RonaAnimator> pAnim;		// Animation

	/*-------------------------------------
	 ���L�����N�^�[�I�u�W�F�N�g�̐e�q�֌W
	 �x�[�X�i�[���R�j
	   - �̂̃I�u�W�F�N�g�i�[���Q�j
		 - ���̃W���C���g�i�[���P�j
		   - ���̃I�u�W�F�N�g�i�q�j
		   - �����i�i�q�j�@�@�@�@�@�@�@// ������
		 - �E��̃W���C���g�i�[���P�j
		 �@- �E��̃I�u�W�F�N�g�i�q�j
		 - ����̃W���C���g�i�[���P�j
		 �@- ����̃I�u�W�F�N�g�i�q�j
		 - �E���̃W���C���g�i�[���P�j
		 �@- �E���̃I�u�W�F�N�g�i�q�j
		 - �����̃W���C���g�i�[���P�j
		 �@- �����̃I�u�W�F�N�g�i�q�j
	 -------------------------------------*/

	 //------------------------------------
	 //--- �L�����N�^�[�̃x�[�X���쐬
	pParent3Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona", TagName::Enemy);
	// ����p�R���|�[�l���g��ǉ�
	pParent3Obj->AddComponent<RonaController>();
	// �X�e�[�^�X��ǉ��A�����X�e�[�^�X��o�^
	pParent3Obj->AddComponent<Status>()->SetInitStatus(
		Status::CharacterType::Enemy,
		mc_nInitLevel,
		mc_nInitExperienceMax,
		mc_nInitAttack,
		mc_nInitDefense,
		mc_nInitSpeed,
		mc_nInitMpMax,
		mc_nInitHpMax);
	// �v���C���[�A�j���[�V������ǉ��A�|�C���^�̎擾
	pAnim = pParent3Obj->AddComponent<RonaAnimator>();
	// Rigidbody��ǉ�
	pParent3Obj->AddComponent<Rigidbody>();
	// AABBCollider��ǉ����A�|�C���^���擾
	pAABBCollider = pParent3Obj->AddComponent<AABBCollider>();
	// �����蔻��̃T�C�Y��ݒ�
	pAABBCollider->SetLen({ mc_sizeX, mc_sizeY, mc_sizeZ });
	// ���W��ݒ�
	pParent3Obj->GetComponent<Transform>()->SetPosition({ 2.0f, 0.0f, 0.0f });

	//------------------------------------
	//--- �̂̃I�u�W�F�N�g���쐬
	pParent2Obj = ObjectManager::CreateObject<Object3D>("Object_Tera_Rona");
	// ���f���̓ǂݍ���
	pParent2Obj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Body_WHITE.fbx", 0.7f);
	// Transform�̃|�C���^���擾
	pTransform = pParent2Obj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f , 0.0f, 0.0f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pParent2Obj->SetParent(pParent3Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pParent2Obj->GetComponent<Transform>()->IsRoot(false);
	// �̂̐F�����F�ɂ���
	pParent2Obj->GetComponent<MeshRenderer>()->SetColor({ 0.2f, 0.2f, 0.2f });
	// �W���C���g���Z�b�g����
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_BODY, pParent2Obj);

	//------------------------------------
	//--- ���̃W���C���g���쐬
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Head_Joint");
	// Transform�̃|�C���^���擾
	pTransform = pParent1Obj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f , 0.5f, 0.0f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pParent1Obj->SetParent(pParent2Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �W���C���g���Z�b�g����
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_HEAD, pParent1Obj);

	//------------------------------------
	//--- ���̃I�u�W�F�N�g���쐬
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Head");
	// ���f���̓ǂݍ���
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Head_WHITE.fbx", 1.0f);
	// Transform�̃|�C���^���擾
	pTransform = pChildObj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f ,0.5f, 0.0f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pChildObj->SetParent(pParent1Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �̂̐F�����F�ɂ���
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });

	//------------------------------------
	//--- �E��̃W���C���g���쐬
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Right_Hand_Joint");
	// Transform�̃|�C���^���擾
	pTransform = pParent1Obj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f , 0.2f, 0.4f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pParent1Obj->SetParent(pParent2Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �W���C���g���Z�b�g����
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_RIGHT_HAND, pParent1Obj);

	//------------------------------------
	//--- �E��̃I�u�W�F�N�g���쐬
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Right_Hand");
	// ���f���̓ǂݍ���
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Hand_WHITE.fbx", 0.2f);
	// Transform�̃|�C���^���擾
	pTransform = pChildObj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f, -0.3f, 0.2f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pChildObj->SetParent(pParent1Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �̂̐F�����F�ɂ���
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });

	//------------------------------------
	//--- ����̃W���C���g���쐬
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Left_Hand_Joint");
	// Transform�̃|�C���^���擾
	pTransform = pParent1Obj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f , 0.2f, -0.4f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pParent1Obj->SetParent(pParent2Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �W���C���g���Z�b�g����
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_LEFT_HAND, pParent1Obj);

	//------------------------------------
	//--- ����̃I�u�W�F�N�g���쐬
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Left_Hand");
	// ���f���̓ǂݍ���
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Hand_WHITE.fbx", 0.2f);
	// Transform�̃|�C���^���擾
	pTransform = pChildObj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f, -0.3f, -0.2f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pChildObj->SetParent(pParent1Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �̂̐F�����F�ɂ���
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });

	//------------------------------------
	//--- �E���̃W���C���g���쐬
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Right_Leg_Joint");
	// Transform�̃|�C���^���擾
	pTransform = pParent1Obj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f , -0.2f, 0.3f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pParent1Obj->SetParent(pParent2Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �W���C���g���Z�b�g����
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_RIGHT_LEG, pParent1Obj);

	//------------------------------------
	//--- �E���̃I�u�W�F�N�g���쐬
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Right_Leg");
	// ���f���̓ǂݍ���
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Leg_WHITE.fbx", 0.2f);
	// Transform�̃|�C���^���擾
	pTransform = pChildObj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f , -0.5f, 0.0f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pChildObj->SetParent(pParent1Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �̂̐F�����F�ɂ���
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });

	//------------------------------------
	//--- �����̃W���C���g���쐬
	pParent1Obj = ObjectManager::CreateObject<ObjectBase>("Object_Rona_Left_Leg_Joint");
	// Transform�̃|�C���^���擾
	pTransform = pParent1Obj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f , -0.2f, -0.3f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pParent1Obj->SetParent(pParent2Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �W���C���g���Z�b�g����
	pAnim->SetJoint(RonaAnimator::TERA_JOINT_INDEX::TERA_JOINT_LEFT_LEG, pParent1Obj);

	//------------------------------------
	//--- �����̃I�u�W�F�N�g���쐬
	pChildObj = ObjectManager::CreateObject<Object3D>("Object_Rona_Left_Leg");
	// ���f���̓ǂݍ���
	pChildObj->GetComponent<MeshRenderer>()->LoadModel("Assets/Model/Character/Leg_WHITE.fbx", 0.2f);
	// Transform�̃|�C���^���擾
	pTransform = pChildObj->GetComponent<Transform>();
	// ���Έʒu���Z�b�g����
	pTransform->SetJointPos({ 0.0f , -0.5f, 0.0f });
	// �e�I�u�W�F�N�g���Z�b�g����
	pChildObj->SetParent(pParent1Obj);
	// �q�I�u�W�F�N�g�̐ݒ�ɂ���
	pTransform->IsRoot(false);
	// �̂̐F�����F�ɂ���
	pChildObj->GetComponent<MeshRenderer>()->SetColor({ 0.3f, 0.3f, 0.3f });
}

// �f�X�g���N�^
RonaObj::~RonaObj()
{

}