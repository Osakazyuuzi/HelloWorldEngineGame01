#include "ColliderBase.h"
#include "ObjectBase.h"
#include "ColliderManager.h"

void ColliderBase::LateUpdate()
{
	ColliderManager::SetCollider(this);
}

void ColliderBase::CheckTouchCollider(ColliderBase* collider)
{
	// �O�t���[���ɐG��Ă������`�F�b�N����
	ColliderBase::ColliderPool::iterator it;
	for (it = m_TouchingPool.begin(); it != m_TouchingPool.end(); it++)
		if ((*it) == collider) break;

	// ��L�ň���������Ȃ�������
	if (it == m_TouchingPool.end())
	{
		// CollisionEnter�Ăяo��
		GetOwner()->CallCollisionEnter(collider->GetOwner());
		collider->GetOwner()->CallCollisionEnter(GetOwner());
		// �ڐG���X�g�ɒǉ�
		m_TouchingPool.push_back(collider);
		collider->m_TouchingPool.push_back(this);
	}

	// CollisionStay�Ăяo��
	GetOwner()->CallCollisionStay(collider->GetOwner());
	collider->GetOwner()->CallCollisionStay(GetOwner());

	// �ڐG���X�g�ɒǉ�
	m_justTouchedPool.push_back(collider);
	collider->m_justTouchedPool.push_back(this);
}

void ColliderBase::CheckExitCollider()
{
	// ������G��Ă���R���C�_�[
	for (auto It = m_TouchingPool.begin(); It != m_TouchingPool.end(); /*++It*/)
	{
		// ���G�ꂽ�R���C�_�[
		ColliderPool::iterator justIt;
		for (justIt = m_justTouchedPool.begin(); justIt != m_justTouchedPool.end(); ++justIt)
		{
			// ���������G��Ă����甲����
			if ((*It) == (*justIt)) break;
		}
		// ��L�ň���������Ȃ�������
		//  ���͐G��Ăč��͐G��Ă��Ȃ�
		if (justIt == m_justTouchedPool.end())
		{
			// CollisionExit�Ăяo��
			GetOwner()->CallCollisionExit((*It)->GetOwner());
			(*It)->GetOwner()->CallCollisionExit(GetOwner());
				
			// �ڐG���X�g���珜�O
			(*It)->m_TouchingPool.remove(this);
			It = m_TouchingPool.erase(It);
		}
		else
		{
			++It;
		}
	}
	// ���t���[���̐ڐG���X�g���폜
	m_justTouchedPool.clear();
}

// �������ɓ��e���ꂽ���������瓊�e���������Z�o
float ColliderBase::LenSegOnSeparateAxis(Float3 *Sep, Float3 *e1, Float3 *e2, Float3 *e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	Sep->normalize();
	float r1 = fabs(Sep->dot(*e1));
	float r2 = fabs(Sep->dot(*e2));
	float r3 = e3 ? fabs(Sep->dot(*e3)) : 0;
	return r1 + r2 + r3;
}