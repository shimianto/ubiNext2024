#pragma once
#include <vector>
#include "../../../Math/Triangle/Triangle.h"
#include "../../../Graphics3D/Color/Color.h"

class Mesh
{
  private:
  
  public:

      Color col;
	  std::vector<Triangle> triangles;
	  std::vector<Triangle> LoadTrianglesFromObjectFile (std::string file);
};

