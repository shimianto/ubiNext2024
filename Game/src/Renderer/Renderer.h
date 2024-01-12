#pragma once
#include "..\Graphics3D\Mesh.h"
#include "..\Math\Matrix.h"

class Renderer
{
 private:
	Mesh cube;

	float fTheta;
  
 public:

	Renderer();
    void Init (float fNear = 0.1f, float fFar = 1000.0f, float fFov = 90.0f);
    void Update(float deltaTime);
    void Render();
};
