#include "LoadUIController.h"
#include "Input.h"
#include "ObjectManager.h"

void LoadUIController::Update()
{
	if (IsKeyPress(VK_SPACE)) {
		ObjectManager::RemoveObject(GetOwner()->GetThisPtr());
	}
}