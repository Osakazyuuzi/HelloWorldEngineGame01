#include "RonaIconController.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "SpriteRenderer.h"

void RonaIconController::Start()
{
	m_pStatus = ObjectManager::FindObjectWithTag(TagName::Enemy)->GetComponent<Status>();
}

void RonaIconController::Update()
{
	GetOwner()->GetComponent<Transform>()->SetPosition({
		GetOwner()->GetComponent<Transform>()->GetPosition().x,
		mc_InitPos - m_pStatus->GetActionGage() * 3,
		GetOwner()->GetComponent<Transform>()->GetPosition().z
		});
}