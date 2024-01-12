#pragma once
#include "..\Graphics3D\Mesh\Mesh.h"
#include "..\Math\Matrix\Matrix.h"

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
