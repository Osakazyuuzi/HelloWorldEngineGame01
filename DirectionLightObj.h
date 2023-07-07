#ifndef ___DIRECTIONLIGHT_OBJ_H___
#define ___DIRECTIONLIGHT_OBJ_H___

#include "ObjectBase.h"
#include <string>
#include "DirectionLight.h"
#include "ConstantBuffer.h"
#include <DirectXMath.h>

class DirectionLightObj : public ObjectBase
{
public:
	// �R���X�g���N�^
	DirectionLightObj(std::string name, std::string tag) : ObjectBase(name, tag)
	{
		AddComponent<DirectionLight>();
	}
	// �f�X�g���N�^
	virtual ~DirectionLightObj()
	{
	}
};

#endif //!___DIRECTIONLIGHT_H___