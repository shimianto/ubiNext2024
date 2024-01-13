#pragma once
#include <vector>
#include "..\..\Math\Math.h"

enum MeshTypes
{
  CUBE
};

class Mesh
{
  public:
  std::vector<Triangle> triangles;

  Mesh ();

  static std::vector<Triangle> LoadTrianglesFromObjectFile (std::string file);
  
  void Update (float deltaTime);
  void Render();


  private:
  //Matrix matRotZ, matRotX;
  std::vector<Triangle> visibleTriangles;
      float fTheta;

  void DrawMesh();
  void RotateMesh (float fTheta);
  void UpdateVisibleTriangles (float deltaTime);
  void SortVisibleTriangles();
};

