#include "stdafx.h"
#include "ParticleSystem.h"
#include "../../../Graphics3D/Graphics3D.h"
#include "Particle.h"
#include "../../../Math/Utils/Utils.h"

template class Pool<Particle>;


ParticleSystem::ParticleSystem() : particleLife_ (100), particlesScale_ (1)
{
}

void ParticleSystem::SpawnParticles (const int &num, const Vector3 &pos, const Vector3 &direction, const Color &col)
{
  mesh.col = col;
  for (int i = 0; i < num; i++) {
	NewParticle (pos, direction, col);
  }
}

void ParticleSystem::NewParticle (const Vector3 &pos, const Vector3 &direction, const Color &col)
{
  int id = particlePool.InstantiateNextAvailable();

  if (id == -1) {
	return;
  }

  Particle &p = particlePool.GetElementByID (id);
  p.lifeTime = particleLife_;
  p.transform.position = pos;
  p.transform.scale = Vector3 (1, 1, 1) * particlesScale_;
  p.velocity.x = direction.x * Utils::RandFloat() * 2.0f;
  p.velocity.y = direction.y * Utils::RandFloat() * 2.0f;
  p.velocity.z = Utils::RandFloat();
  p.color = col;
}

void ParticleSystem::Update (const float &deltaTime)
{
  std::set<int> activeParticles = particlePool.GetInUseElements(); 
  for (const auto &id : activeParticles) {
	bool isDone = particlePool.GetElementByID (id).animate();
	
	if (isDone) {
	  particlePool.DisableElement (id);
	}
  }
}

void ParticleSystem::Render2D()
{
  for (const auto &id : particlePool.GetInUseElements()) {
	Particle p = particlePool.GetElementByID (id);

	Graphics3D::DrawTriangle((p.triangle2D + p.transform.position), p.color);
  }
}

bool ParticleSystem::HasActiveParticles()
{
  return particlePool.GetInUseElements().size() > 0;
}

void ParticleSystem::SetParticleLife (const int &life)
{
  particleLife_ = life;
}

void ParticleSystem::SetParticleScale (const float &scale)
{
  particlesScale_ = scale;
}
