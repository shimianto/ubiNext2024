#pragma once
#include "Triangle.h"
#include <vector>

namespace Graphics3D {
enum MeshTypes
{
  CUBE
};

class Mesh
{
  public:
  std::vector<Triangle> triangles;

  Mesh (MeshTypes type = CUBE);

  private:
  void SetCubeMesh();
};
}
