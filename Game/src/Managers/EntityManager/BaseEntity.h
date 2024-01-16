#pragma once
#include "../../Graphics3D/Mesh/Mesh.h"

class BaseEntity
{
  friend class EntityManager;
  private:
  
      int m_id;
      bool m_isActive;


  public:
      Mesh mesh;
  
      BaseEntity();
      int GetId();
      bool IsActive();
      void SetActive (bool active);
};
