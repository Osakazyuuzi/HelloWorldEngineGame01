#ifndef ___CAMERA_BASE_H___
#define ___CAMERA_BASE_H___

#include "ObjectBase.h"
#include <string>
//#include "Camera.h"
#include "CameraDebug.h"

class CameraObjBase : public ObjectBase
{
public:
	// �R���X�g���N�^
	CameraObjBase(std::string name, std::string tag) : ObjectBase(name, tag)
	{

	}
	// �f�X�g���N�^
	virtual ~CameraObjBase() {}

	//--- �J�����^�O�Ǘ��p
	void SetTag(std::string tag) { m_tag = tag; }	// �^�O�A�N�Z�T�[
	void ChangeToMainCamera();	// ���C���J�����ɕύX
};

#endif //!___CAMERA_BASE_H___