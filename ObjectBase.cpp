#include "ObjectBase.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "ColliderManager.h"

// �R���X�g���N�^
ObjectBase::ObjectBase()
	: m_name("Object")
	, m_tag(TagName::Untagged)
	, m_isDestroy(false)
	, m_Parent(nullptr)
	, m_LayerNum(0)
{
	// �f�t�H���g�R���|�[�l���g��ǉ�
	AddComponent<Transform>();
}

// �X�V
void ObjectBase::Update() {
	for (auto it = m_ComponentPool.begin(); it != m_ComponentPool.end(); it++)
		(*it)->Update();
}

// �I�u�W�F�N�g���폜����
void ObjectBase::Destroy() {
	ObjectManager::RemoveObject(static_cast<std::shared_ptr<ObjectBase>>(this));
}

// ���C���[�ԍ��ɂ���r
bool operator<(const std::shared_ptr<ObjectBase>& left, const std::shared_ptr<ObjectBase>& right)
{
	return left->GetLayerNum() < right->GetLayerNum();
}
bool operator>(const std::shared_ptr<ObjectBase>& left, const std::shared_ptr<ObjectBase>& right)
{
	return left->GetLayerNum() > right->GetLayerNum();
}