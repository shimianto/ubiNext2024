#include "stdafx.h"
#include "GridElement.h"

GridElement::GridElement (const UIBar &suface) : 
	surface2d_(suface)
{
}

GridElement::GridElement (const Vector3 &position, const Vector3 &size, const float &fill, const Color &color) : 
	surface2d_(position, size, fill, color)
{
}

const UIBar &GridElement::Get2DSurface() const 
{
  return surface2d_;
}
