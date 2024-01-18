#pragma once
#include <vector>
#include "GridElement.h"
class Grid
{
  private:
  
      bool initialized_;
	  int height_, width_;
      std::vector<GridElement> grid_;
      Vector3 position_;
      Vector3 cellSize_;

  public:
      Grid();
	  void Init (const int &width, const int &height, const Vector3 &cellSize, const Vector3 &pos = Vector3());
      GridElement &GetElement (const int &x, const int &y);

	  void DrawGrid2D();
};
