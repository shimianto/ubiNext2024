#pragma once
#include "../Components/Mesh/Mesh.h"
#include "../Components/Health/Health.h"
#include "../Components/Transform/Transform.h"

class BaseEntity
{
  friend class EntityManager;
  private:
  
      int m_id;
      bool m_isActive;


  public:  
      BaseEntity();
      int GetId();
      bool IsActive();
      void SetActive (bool active);
};
