#ifndef ___COLLIDERMANAGER_H___
#define ___COLLIDERMANAGER_H___

#include "ColliderBase.h"
#include <list>

class ColliderManager
{
public:
	// �R���X�g���N�^
	ColliderManager(){}
	// �f�X�g���N�^
	~ColliderManager(){}

	// �X�V
	static void Update();
	// �����蔻���o�^
	static void SetCollider(ColliderBase* collider) {
		m_ColliderList.push_back(collider);
	}

private:
	// �����蔻�胊�X�g
	static std::list<ColliderBase*> m_ColliderList;
};

#endif //!___COLLIDERMANAGER_H___