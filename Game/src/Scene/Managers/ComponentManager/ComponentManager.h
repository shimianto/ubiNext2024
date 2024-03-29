#pragma once
#include <vector>
#include "../../Components/Mesh/Mesh.h"
#include "../../Components/Transform/Transform.h"
#include "../../Components/Health/Health.h"
#include "../../Components/Particles/ParticleSystem.h"
#include "../../Components/Grid/Grid.h"
#include "../../Components/AI/BaseAI.h"
#include "../../Components/Collider/Collider.h"
#include "../../Components/Physics/Physics.h"

class ComponentManager
{
  private:
  
	  int nextValidIndex_;
	  std::vector<Mesh> meshComponents_;
	  std::vector<Health> healthComponents_;
      std::vector<Transform> transformComponents_;
      std::vector<ParticleSystem> particlesComponents_;
      std::vector<Grid> gridComponents_;
      std::vector<BaseAI> baseAIComponents_;
      std::vector<Collider> colliderComponents_;
      std::vector<Physics> physicsComponents_;

  public:
      ~ComponentManager();

	  void InstantiateComponents(const int &id);

      Mesh &GetMeshFromID (const int &id);
      Health &GetHealthFromID (const int &id);
      Transform &GetTransformFromID (const int &id);
      ParticleSystem &GetParticlesFromID (const int &id);
      Grid &GetGridFromID (const int &id);
      BaseAI &GetAIFromID (const int &id);
      Collider &GetColliderFromID (const int &id);
      Physics &GetPhysicsFromID (const int &id);

	  void ClearComponents();
};
