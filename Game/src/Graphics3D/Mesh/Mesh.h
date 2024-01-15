#pragma once
#include <vector>
#include "..\..\Math\Math.h"
#include "..\..\Managers\EntityManager\BaseEntity.h"

class Mesh : BaseEntity
{
  public:
  std::vector<Triangle> triangles;

  using BaseEntity::BaseEntity;
  std::vector<Triangle> LoadTrianglesFromObjectFile (std::string file);

};

