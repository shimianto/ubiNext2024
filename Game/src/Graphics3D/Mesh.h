#pragma once
#include "Triangle.h"
#include <vector>

enum MeshTypes
{
  CUBE
};

class Mesh
{
  public:
  std::vector<Triangle> triangles;

  Mesh (MeshTypes type = CUBE);

  static void InitProjectionMatrix (float fNear, float fFar, float fFov);
  
  void Update (float deltaTime, float ftheta);
  void Render();

  private:
  Matrix matRotZ, matRotX;
  static Matrix projectionMatrix;
  static float fNear, fFar, fFov;

  void DrawMesh();
  void RotateMesh (float fTheta);
  void SetCubeMesh();
};

