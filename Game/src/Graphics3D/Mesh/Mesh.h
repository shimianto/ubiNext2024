#pragma once
#include <vector>
#include "..\..\Math\Math.h"

class Mesh
{
  public:
  std::vector<Triangle> triangles;

  Mesh ();

  std::vector<Triangle> LoadTrianglesFromObjectFile (std::string file);

};

