#pragma once
#include <vector>
#include "..\..\Math\Triangle\Triangle.h"

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
  
  void Update (float deltaTime, float ftheta);
  void Render();


  private:
  Matrix matRotZ, matRotX;
  std::vector<Triangle> visibleTriangles;

  void DrawMesh();
  void RotateMesh (float fTheta);
  void UpdateVisibleTriangles();
  void SortVisibleTriangles();
};

