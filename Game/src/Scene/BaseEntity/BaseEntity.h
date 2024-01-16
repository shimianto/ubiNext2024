#pragma once
#include "../../Graphics3D/Mesh/Mesh.h"
#include "../Components/Health/Health.h"

class BaseEntity
{
  friend class EntityManager;
  private:
  
      int m_id;
      bool m_isActive;


  public:
      Mesh mesh;
      Health health;
  
      BaseEntity();
      int GetId();
      bool IsActive();
      void SetActive (bool active);
};
