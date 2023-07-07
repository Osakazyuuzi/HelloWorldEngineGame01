#ifndef ___CAMERAOBJ_PLAYER_H___
#define ___CAMERAOBJ_PLAYER_H___
#include "CameraObjBase.h"
#include <string>
#include "CameraPlayer.h"

class CameraObjPlayer : public CameraObjBase
{
public:
	// �R���X�g���N�^
	CameraObjPlayer(std::string name, std::string tag) : CameraObjBase(name, tag)
	{
		// �R���|�[�l���g�ǉ�
		AddComponent<CameraPlayer>();
	}
	// �f�X�g���N�^
	virtual ~CameraObjPlayer(){}
};


#endif //!___CAMERAOBJ_PLAYER_H___