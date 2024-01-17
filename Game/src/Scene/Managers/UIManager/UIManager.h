#pragma once
#include <map>
#include "../../UI/UI.h"
#include "../../Scene.h"

class UIManager
{
  private:
	std::map<SceneType, UI> m_uiMap;

  public:

      void Init (const Scene &scene);
      void Update(const Scene &scene);
      void Render (const Scene &scene);

	  void RegisterUI (const SceneType &screen, UI &ui);
      UI GetActiveUI (const Scene &scene);
};
