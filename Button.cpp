#include "Button.h"
#include "input.h"
#include "SceneManager.h"

void Button::Update()
{
	if (IsKeyTrigger(VK_SPACE))
	{
		SceneManager::LoadScene(SceneName::SceneName::SceneGame);
	}
}