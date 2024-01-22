#include <algorithm>
#include "Renderer.h"
#include "../Scene/Scene.h"
#include "../Scene/Components/Mesh/Mesh.h"
#include "../Graphics3D/Camera/Camera.h"
#include "../Graphics3D/Color/Color.h"
#include "../Graphics3D/Graphics3D.h"
#include "../Math/Matrix/Matrix.h"
#include "../ThreadGroup/ThreadGroup.h"

Renderer::Renderer()
{
}

void Renderer::Init (Scene &scene)
{
  scene_ = &scene;
  matProj_ = Matrix::MakeProjectionMatrix(FOV_, NEAR_, FAR_);
}

void Renderer::Update (const float &deltaTime)
{
  SetWorldMatrix();
  SetViewMatrices();

  visibleTriangles_.clear();


  for (auto id : scene_->GetActiveEntities()) {
	SetVisibleTriangles (scene_->components.GetMeshFromID (id), scene_->components.GetTransformFromID (id));
	ParticleSystem &ps = scene_->components.GetParticlesFromID (id);
	
	//Add Particles to visible triangles
	for (const auto &particleId : ps.particlePool.GetInUseElements()) {
		SetVisibleTriangles (ps.mesh, ps.particlePool.GetElementByID(particleId).transform);
	  }
  }
}

void Renderer::SetWorldMatrix()
{
  matWorld_ = 
	  Matrix::MakeRotationMatrix (Vector3()) * 
	  Matrix::Translate (CAMERA_DEFAULT_TRANSLATION_);
}
void Renderer::SetViewMatrices()
{
  Matrix matCamRotation = Matrix::MakeRotationMatrix (Camera::mainCamera.transform.rotation);

  Vector3 vForward = ((Camera::mainCamera.target) * matCamRotation).Normalize();
  Vector3 vRight = Vector3::CrossProduct (vForward, Camera::mainCamera.transform.up).Normalize();
  Vector3 vUp = Vector3::CrossProduct (vRight, vForward);

  // Construct View Matrix based on Camera data
  viewMat_.m[0][0] = vRight.x;
  viewMat_.m[0][1] = vUp.x;
  viewMat_.m[0][2] = vForward.x;
  viewMat_.m[0][3] = 0.0f;
  viewMat_.m[1][0] = vRight.y;
  viewMat_.m[1][1] = vUp.y;
  viewMat_.m[1][2] = vForward.y;
  viewMat_.m[1][3] = 0.0f;
  viewMat_.m[2][0] = vRight.z;
  viewMat_.m[2][1] = vUp.z;
  viewMat_.m[2][2] = vForward.z;
  viewMat_.m[2][3] = 0.0f;
  viewMat_.m[3][0] = -(vRight * Camera::mainCamera.transform.position);
  viewMat_.m[3][1] = -(vUp * Camera::mainCamera.transform.position);
  viewMat_.m[3][2] = -(vForward * Camera::mainCamera.transform.position);
}

void Renderer::SetVisibleTriangles (const Mesh &mesh, const Transform &transform)	
{
  Matrix localTransformedMat = Matrix::MakeTransformedMatrix (transform);

  for (auto tri : mesh.triangles) {
	Triangle triTransformed;
	Triangle triViewed;
	Triangle triProjected;

	for (int i = 0; i < 3; i++) {
		// Transform triangles
		triTransformed.vertices[i] = (tri.vertices[i] * localTransformedMat) * matWorld_;
		// Get triangles in view space
		triViewed.vertices[i] = triTransformed.vertices[i] * viewMat_;
		//Turn into 2D
		triProjected.vertices[i] = triViewed.vertices[i] * matProj_;
	    triProjected.vertices[i] = triProjected.vertices[i] / triProjected.vertices[i].w;

		//Scale in screen space
		triProjected.vertices[i] += Vector3(1,1,0);
	    triProjected.vertices[i].x *= 0.5f * (float)APP_INIT_WINDOW_WIDTH;
	    triProjected.vertices[i].y *= 0.5f * (float)APP_INIT_WINDOW_HEIGHT;
	}

	// Render if in view
	if (!IsBehindCamera(triTransformed) && !IsTriangleClipped ({0.0f, 0.0f, NEAR_}, {0.0f, 0.0f, 1.0f}, triViewed)) {
	  triProjected.col = mesh.col;
	  visibleTriangles_.push_back (triProjected);
	}
  }
}

void Renderer::Render()
{
  DrawVisibleTriangles();
}
void Renderer::DrawVisibleTriangles()
{
  for (auto &tri : visibleTriangles_) {
	Color lineCol = tri.col.a ? Color (0, 0, 0) : tri.col;

	App::DrawLine (tri.vertices[0].x, tri.vertices[0].y, tri.vertices[1].x, tri.vertices[1].y, lineCol.r, lineCol.g, lineCol.b);
	App::DrawLine (tri.vertices[1].x, tri.vertices[1].y, tri.vertices[2].x, tri.vertices[2].y, lineCol.r, lineCol.g, lineCol.b);
	App::DrawLine (tri.vertices[2].x, tri.vertices[2].y, tri.vertices[0].x, tri.vertices[0].y, lineCol.r, lineCol.g, lineCol.b);

	if (tri.col.a) {
	  Graphics3D::DrawTriangle (tri, tri.col);
	}
  }
}

bool Renderer::IsBehindCamera (Triangle &triTransformed)
{
	 return triTransformed.GetSurfaceNormal().Normalize() * (triTransformed.vertices[0] - Camera::mainCamera.transform.position) >= 0.0f;
}

bool Renderer::IsTriangleClipped (Vector3 point, Vector3 normal, Triangle &triangle)
{
  // Count how many vertices lie on inside of plane
  int count = 0;
  float dot = normal * point;
  for (int i = 0; i < 3; i++) {
	Vector3 vertex = triangle.vertices[i];
	float distance = normal.x * vertex.x + normal.y * vertex.y + normal.z * vertex.z - dot;
	if (distance >= 0) {
	    count++;
	}
  }

  // If not all, then clip
  return count != 3;
}

