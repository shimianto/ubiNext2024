#include "stdafx.h"
#include "ParticleSystem.h"
#include "../../../Graphics3D/Graphics3D.h"
#include "Particle.h"
#include "../../Systems/Systems.h"

template class Pool<Particle>;


void ParticleSystem::NewParticle (const Vector3 &pos)
{
  int id = particlePool_.InstantiateNextAvailable();

  if (id == -1) {
	return;
  }

  Particle &p = particlePool_.GetElementByID (id);
  p.lifeTime = 100;
  p.position = pos;
  p.velocity = Vector3 (Systems::RandInt (-2, 2), Systems::RandInt (-2, 2));
  //p.color = Color (Systems::RandFloat(), Systems::RandFloat(), Systems::RandFloat());
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

	Graphics3D::DrawTriangle((p.tri + p.position), p.color);
  }
}
