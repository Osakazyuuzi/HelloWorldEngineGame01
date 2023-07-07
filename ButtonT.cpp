#include "ButtonT.h"
#include "input.h"
#include "SceneManager.h"

void ButtonT::Update()
{
	if (IsKeyTrigger(VK_SPACE))
	{
		SceneManager::LoadScene(SceneName::SceneName::SceneTitle);
	}
}