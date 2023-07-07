#ifndef ___PARTICLE_SYSTEM_H___
#define ___PARTICLE_SYSTEM_H___

#include <memory>
#include <list>
#include "ComponentBase.h"
#include "ObjectBase.h"
#include <DirectXMath.h>
#include "Particle.h"

class ParticleSystem
{
public:

	ParticleSystem(DirectX::XMFLOAT3 spawnPos);

	constexpr static int mc_particleMax = 30;
private:
	DirectX::XMFLOAT3 m_SpawnPos;
};

#endif //!__PARTICLE_SYSTEM_H___