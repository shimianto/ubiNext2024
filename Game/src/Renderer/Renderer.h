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
    void Init ();
    void Update(float deltaTime);
    void Render();
};
