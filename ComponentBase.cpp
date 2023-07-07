#include "ComponentBase.h"
#include "ObjectBase.h"

ComponentBase::ComponentBase()
	: m_Owner(nullptr)
{
}

// �i�[�I�u�W�F�N�g���擾
ObjectBase* ComponentBase::GetOwner() { return m_Owner; }

// �i�[�I�u�W�F�N�g���Z�b�g
void ComponentBase::SetOwner(ObjectBase* Owner) { m_Owner = Owner; }