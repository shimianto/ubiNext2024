#pragma once
#include <vector>
#include "../../../Math/Triangle/Triangle.h"

class Mesh
{
  private:
  
  public:
  
	  std::vector<Triangle> triangles;
	  std::vector<Triangle> LoadTrianglesFromObjectFile (std::string file);
};

