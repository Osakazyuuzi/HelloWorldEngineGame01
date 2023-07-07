#include "Game3D.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Input.h"

Game3D::Game3D()
{
	// �^�C�g���V�[���֕ύX
	SceneManager::LoadScene(SceneName::SceneTitle);
}
Game3D::~Game3D()
{
}
void Game3D::Update()
{
	ObjectManager::FixedUpdate();
	ObjectManager::Update();

	if (IsKeyPress(VK_F1)) SceneManager::LoadScene(SceneName::SceneTitle);
	if (IsKeyPress(VK_F2)) SceneManager::LoadScene(SceneName::SceneGame);


}

void Game3D::LateUpdate()
{
	ObjectManager::LateUpdate();
}

void Game3D::Draw()
{
	ObjectManager::Draw();
}