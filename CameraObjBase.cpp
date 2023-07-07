#include "CameraObjBase.h"
#include "ObjectManager.h"
#include <memory>

// ���C���J�����ɕύX
void CameraObjBase::ChangeToMainCamera()
{
	// MainCamera�̃^�O�������J�����I�u�W�F�N�g��T���A
	// �^�O����MainCamera����Untagged�ɕύX����
	std::shared_ptr<CameraObjBase> pCameraObj;
	pCameraObj = std::reinterpret_pointer_cast<CameraObjBase>(ObjectManager::FindObjectWithTag(TagName::MainCamera));
	pCameraObj->SetTag(TagName::Untagged);

	// �����̃^�O��MainCamera�ɂ���
	this->m_tag = TagName::MainCamera;

	ObjectManager::RemoveObject(pCameraObj->GetThisPtr());
}