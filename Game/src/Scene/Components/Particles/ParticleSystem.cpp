#include "stdafx.h"
#include "ParticleSystem.h"
#include "../../../Graphics3D/Graphics3D.h"
#include "Particle.h"
#include "../../../Math/Utils/Utils.h"

template class Pool<Particle>;


void ParticleSystem::NewParticle (const Vector3 &pos, const Color &col)
{
  int id = particlePool_.InstantiateNextAvailable();

  if (id == -1) {
	return;
  }

  Particle &p = particlePool_.GetElementByID (id);
  p.lifeTime = 100;
  p.position = pos;
  p.velocity = Vector3 (Utils::RandInt (-2, 2), Utils::RandInt (-2, 2));
  p.color = col;
}

void ParticleSystem::Update (const float &deltaTime)
{
  for (const auto &id : particlePool_.GetInUseElements()) {
	bool isDone = particlePool_.GetElementByID (id).animate();
	
	if (isDone) {
	  particlePool_.DisableElement (id);
	}
  }
}

void ParticleSystem::Render()
{
  for (const auto &id : particlePool_.GetInUseElements()) {
	Particle p = particlePool_.GetElementByID (id);

	Graphics3D::DrawTriangle((p.tri + p.position), p.color);
  }
}

bool ParticleSystem::HasActiveParticles()
{
  return particlePool_.GetInUseElements().size() > 0;
}
