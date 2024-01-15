#pragma once

class BaseEntity
{
  friend class EntityManager;
  private:
  
      int m_id;
      bool m_isActive;

  public:
  
      BaseEntity(EntityManager &manager);
      int GetId();
      bool IsActive();
      void SetActive (bool active);
};
