#pragma once
#include "../Components/Mesh/Mesh.h"
#include "../Components/Health/Health.h"
#include "../Components/Transform/Transform.h"

class BaseEntity
{
  friend class EntityManager;
  private:
  
      int id_;
      bool isActive_;


  public:  
      BaseEntity();
      int GetId();
      bool IsActive();
      void SetActive (bool active);
};
