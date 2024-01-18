#pragma once
#include "../../UI/UI.h"
class GridElement
{
	  UIBar surface2d_;

  public:
  
	  GridElement(const UIBar &suface);
      GridElement (const Vector3 &position = Vector3(), const Vector3 &size = Vector3 (1, 1), const float &fill = 1, const Color &color = Color());
      const UIBar &Get2DSurface() const;
};
