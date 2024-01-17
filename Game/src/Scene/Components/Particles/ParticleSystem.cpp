#include "stdafx.h"
#include "ParticleSystem.h"
#include "../../../Graphics3D/Graphics3D.h"
#include "Particle.h"

template class Pool<Particle>;


void ParticleSystem::NewParticle (Transform t)
{
  int id = particlePool_.InstantiateNextAvailable();

  if (id == -1) {
	return;
  }

  Particle &p = particlePool_.GetElementByID (id);
  p.lifeTime = 100;
  p.transform = t;
  p.velocity = Vector3();
}

void ParticleSystem::Update (float deltaTime)
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

	Graphics3D::DrawTriangle((p.tri + p.transform.position), Color(1, 0 , 0));
  }
}
