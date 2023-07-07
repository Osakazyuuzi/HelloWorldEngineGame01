#ifndef ___CUBE_H___
#define ___CUBE_H___
#include "Object3D.h"
#include "MeshRenderer.h"

class Cube : public Object3D
{
public:
	// �R���X�g���N�^
	Cube(std::string name, std::string tag) : Object3D(name, tag) {
		// �L���[�u�̃��f�������[�h����
		GetComponent<MeshRenderer>()->LoadModel("Assets/Model/DemoCube/DemoCube10.fbx", 1.0f);
	}
	// �f�X�g���N�^
	~Cube(){}
};

#endif //!___CUBE_H___