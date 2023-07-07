#include "CameraPlayer.h"
#include "Transform.h"
#include "ObjectManager.h"
#include "CameraObjBase.h"

void CameraPlayer::Update()
{

	// Player�^�O�̂����I�u�W�F�N�g�̍��W���擾���A�����_�ɂ���B
	m_LookPoint = {
		ObjectManager::FindObjectWithTag(TagName::Player)->GetComponent<Transform>()->GetPosition().x,
		ObjectManager::FindObjectWithTag(TagName::Player)->GetComponent<Transform>()->GetPosition().y + 1.5f,
		ObjectManager::FindObjectWithTag(TagName::Player)->GetComponent<Transform>()->GetPosition().z
	};

	// �p�x�Ƌ����A�����_����J�����̈ʒu���v�Z
	GetOwner()->GetComponent<Transform>()->SetPosition({
	cosf(m_radY) * sinf(m_radXZ) * m_radius + m_LookPoint.x,
	sinf(m_radY) * m_radius + m_LookPoint.y,
	cosf(m_radY) * cosf(m_radXZ) * m_radius + m_LookPoint.z
		});
}