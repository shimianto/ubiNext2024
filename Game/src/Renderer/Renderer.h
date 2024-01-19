#pragma once
#include <list>
#include <App/app.h>

#include "../Scene/Components/Mesh/Mesh.h"
#include "..\Graphics3D\Camera\Camera.h"
#include "..\Math\Matrix\Matrix.h"
#include "../Scene/Components/Transform/Transform.h"
#include <list>

class Scene;

class Renderer
{
 private:
     const float FOV_ = 90.0f;
     const float NEAR_ = 0.1f; 
     const float FAR_ = 1000.0f; 
     const Vector3 CAMERA_DEFAULT_TRANSLATION_ = Vector3 (0.0f, 0.0f, 8.0f);

     Scene *scene_;
     std::vector<Triangle> visibleTriangles_;

     Matrix matWorld_;
     Matrix matProj_;
     Matrix viewMat_, invViewMat_;

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
