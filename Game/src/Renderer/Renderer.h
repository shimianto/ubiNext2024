#pragma once
#include <list>
#include <App/app.h>

#include "..\Graphics3D\Mesh\Mesh.h"
#include "..\Graphics3D\Camera\Camera.h"
#include "..\Math\Matrix\Matrix.h"
#include "../Scene//Components/Transform/Transform.h"

class Scene;

class Renderer
{
 private:
     const float m_FOV = 90.0f;
     const float m_NEAR = 0.1f; 
     const float m_FAR = 1000.0f; 
     const Vector3 m_CAMERA_DEFAULT_TRANSLATION = Vector3 (0.0f, 0.0f, 8.0f);

     Scene *m_scene;
     std::vector<Triangle> m_visibleTriangles;

     Matrix m_matWorld;
     Matrix m_matProj;
     Matrix m_viewMat, m_invViewMat;

     Camera m_camera;

    void SetWorldMatrix();
    void SetViewMatrices();
    void SetVisibleTriangles (const Mesh &mesh, const Transform &transform);
    void SortVisibleTriangles();

    void DrawVisibleTriangles();
    
    Vector3 PlaneInersection (Vector3 &plane_p, Vector3 &plane_n, Vector3 &lineStart, Vector3 &lineEnd);
    int GetNumPtsCliped (Vector3 plane_p, Vector3 plane_n, Triangle &in_tri, Triangle &out_tri1, Triangle &out_tri2);

 public:

	Renderer ();
    void Init (Scene &scene);
    void Update (const float &deltaTime);
    void Render();
};
