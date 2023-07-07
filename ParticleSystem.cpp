#include "ParticleSystem.h"
#include "ObjectManager.h"
#include "ObjectBase.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "UI.h"

ParticleSystem::ParticleSystem(DirectX::XMFLOAT3 spawnPos)
{
	std::shared_ptr<ObjectBase> pObj;
	for (int i = 0; i < mc_particleMax; i++)
	{
		pObj = ObjectManager::CreateObject<Particle>("Particle");
		pObj->GetComponent<Transform>()->SetPosition(m_SpawnPos);
		pObj->GetComponent<Rigidbody>()->SetAccele({
			((rand() % 100) - 50) * 0.1f,
			((rand() % 100) - 50) * 0.1f,
			((rand() % 100) - 50) * 0.1f });
	}
}
