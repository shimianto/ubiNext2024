#pragma once
#include <vector>
#include "../../Components/Mesh/Mesh.h"
#include "../../Components/Transform/Transform.h"
#include "../../Components/Health/Health.h"

class ComponentManager
{
  private:
  
	  int m_nextValidIndex;
	  std::vector<Mesh> m_meshComponents;
	  std::vector<Health> m_healthComponents;
	  std::vector<Transform> m_transformComponents;

  public:
      ~ComponentManager();

	  void InstantiateComponents(const int &id);

      Mesh &GetMeshFromID (const int &id);
      Health &GetHealthFromID (const int &id);
      Transform &GetTransformFromID (const int &id);

	  void ClearComponents();
};
