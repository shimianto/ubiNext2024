#include "stdafx.h"
#include "App/app.h"
#include "Renderer.h"
#include "../Scene/Components/Mesh/Mesh.h"
#include "..\Math\Matrix\Matrix.h"
#include "../Graphics3D/Camera/Camera.h"
#include <algorithm>
#include "../Graphics3D/Color/Color.h"
#include "../Graphics3D/Graphics3D.h"
#include "../Scene/Scene.h"
#include "../ThreadGroup/ThreadGroup.h"
#include <functional>

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

  ThreadGroup threadGrp;

  for (auto id : scene_->GetActiveEntities()) {
	threadGrp.group.emplace_back (
		&Renderer::SetVisibleTriangles, this, 
		scene_->components.GetMeshFromID (id),
		scene_->components.GetTransformFromID (id)
	);
	
	ParticleSystem &ps = scene_->components.GetParticlesFromID (id);
	if (ps.HasActiveParticles()) {
		threadGrp.group.emplace_back (
			&ParticleSystem::Update, 
			&ps,
			deltaTime
		);
	}
  }

  threadGrp.JoinAll();

  SortVisibleTriangles();
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

  // Calculate new forward direction
  Vector3 vForward = ((Camera::mainCamera.target) * matCamRotation).Normalize();
  // Calculate new right direction
  Vector3 vRight = Vector3::CrossProduct (vForward, Camera::mainCamera.transform.up).Normalize();
  // Calculate new Up direction
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

  // Invert View Matrix
  invViewMat_.m[0][0] = vRight.x;
  invViewMat_.m[0][1] = vRight.y;
  invViewMat_.m[0][2] = vRight.z;
  invViewMat_.m[0][3] = 0.0f;
  invViewMat_.m[1][0] = vUp.x;
  invViewMat_.m[1][1] = vUp.y;
  invViewMat_.m[1][2] = vUp.z;
  invViewMat_.m[1][3] = 0.0f;
  invViewMat_.m[2][0] = vForward.x;
  invViewMat_.m[2][1] = vForward.y;
  invViewMat_.m[2][2] = vForward.z;
  invViewMat_.m[2][3] = 0.0f;
  invViewMat_.m[3][0] = Camera::mainCamera.transform.position.x;
  invViewMat_.m[3][1] = Camera::mainCamera.transform.position.y;
  invViewMat_.m[3][2] = Camera::mainCamera.transform.position.z;
  invViewMat_.m[3][3] = 1.0f;
}

void Renderer::SetVisibleTriangles (const Mesh &mesh, const Transform &transform)	
{
  Matrix localTransformedMat = Matrix::MakeTransformedMatrix (transform);

  for (auto tri : mesh.triangles) {
	Triangle triTransformed;

	// World Matrix Transform
	triTransformed.vertices[0] = (tri.vertices[0] * localTransformedMat) * matWorld_;
	triTransformed.vertices[1] = (tri.vertices[1] * localTransformedMat) * matWorld_;
	triTransformed.vertices[2] = (tri.vertices[2] * localTransformedMat) * matWorld_;

	// Use Cross-Product to get surface2d_ normal
	Vector3 normal = triTransformed.GetSurfaceNormal().Normalize();

	if (normal * (triTransformed.vertices[0] - Camera::mainCamera.transform.position) >= 0.0f) {
	  continue;
	}

	Triangle triViewed;

	// Convert World Space --> View Space
	triViewed.vertices[0] = triTransformed.vertices[0] * viewMat_;
	triViewed.vertices[1] = triTransformed.vertices[1] * viewMat_;
	triViewed.vertices[2] = triTransformed.vertices[2] * viewMat_;

	// Clip Viewed Triangle against near plane,
	// this could form two additional additional triangles.
	int nClippedTriangles = 0;
	Triangle clipped[2];
	nClippedTriangles = GetNumPtsCliped ({0.0f, 0.0f, NEAR_}, {0.0f, 0.0f, 1.0f}, triViewed, clipped[0], clipped[1]);

	for (int n = 0; n < nClippedTriangles; n++) {
	  Triangle triProjected;

	  // Project triangles from 3D --> 2D
	  triProjected.vertices[0] = clipped[n].vertices[0] * matProj_;
	  triProjected.vertices[1] = clipped[n].vertices[1] * matProj_;
	  triProjected.vertices[2] = clipped[n].vertices[2] * matProj_;

	  triProjected.vertices[0] = triProjected.vertices[0] / triProjected.vertices[0].w;
	  triProjected.vertices[1] = triProjected.vertices[1] / triProjected.vertices[1].w;
	  triProjected.vertices[2] = triProjected.vertices[2] / triProjected.vertices[2].w;

	  // Scale into view
	  // Offset verts into visible normalised space
	  Vector3 vOffsetView = {1, 1, 0};
	  for (int i = 0; i < 3; i++) {
		triProjected.vertices[i] = triProjected.vertices[i] + vOffsetView;
		triProjected.vertices[i].x *= 0.5f * (float)APP_INIT_WINDOW_WIDTH;
		triProjected.vertices[i].y *= 0.5f * (float)APP_INIT_WINDOW_HEIGHT;
	  }

	  visibleTriangles_.push_back (triProjected);
	}
  }
}
void Renderer::SortVisibleTriangles()
{
  sort (visibleTriangles_.begin(), visibleTriangles_.end(), [] (Triangle &t1, Triangle &t2) {
	float z1 = t1.vertices->Magnitude() / 3.0f;
	float z2 = t2.vertices->Magnitude() / 3.0f;
	return z1 > z2;
  });
}

void Renderer::Render()
{
  for (auto id : scene_->GetActiveEntities()) {
	  scene_->components.GetParticlesFromID (id).Render();
	  scene_->components.GetGridFromID (id).DrawGrid2D();
  }
  DrawVisibleTriangles();
}
void Renderer::DrawVisibleTriangles()
{
  for (auto &triToRaster : visibleTriangles_) {
	// Clip triangles against all four screen edges, this could yield
	// a bunch of triangles, so create a queue that we traverse to
	//  ensure we only test new triangles generated against planes
	Triangle clipped[2];
	std::list<Triangle> listTriangles;

	// Add initial triangle
	listTriangles.push_back (triToRaster);
	int nNewTriangles = 1;

	for (int p = 0; p < 4; p++) {
	  int nTrisToAdd = 0;
	  while (nNewTriangles > 0) {
		// Take triangle from front of queue
		Triangle test = listTriangles.front();
		listTriangles.pop_front();
		nNewTriangles--;

		// Clip it against a plane. We only need to test each
		// subsequent plane, against subsequent new triangles
		// as all triangles after a plane clip are guaranteed
		// to lie on the inside of the plane. I like how this
		// comment is almost completely and utterly justified
		switch (p) {
		case 0:
		  nTrisToAdd = GetNumPtsCliped ({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, test, clipped[0], clipped[1]);
		  break;
		case 1:
		  nTrisToAdd = GetNumPtsCliped ({0.0f, (float)APP_INIT_WINDOW_HEIGHT - 1, 0.0f}, {0.0f, -1.0f, 0.0f}, test, clipped[0], clipped[1]);
		  break;
		case 2:
		  nTrisToAdd = GetNumPtsCliped ({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, test, clipped[0], clipped[1]);
		  break;
		case 3:
		  nTrisToAdd = GetNumPtsCliped ({(float)APP_INIT_WINDOW_WIDTH - 1, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, test, clipped[0], clipped[1]);
		  break;
		}

		// Clipping may yield a variable number of triangles, so
		// add these new ones to the back of the queue for subsequent
		// clipping against next planes
		for (int w = 0; w < nTrisToAdd; w++)
		  listTriangles.push_back (clipped[w]);
	  }
	  nNewTriangles = listTriangles.size();
	}


	// Draw the transformed, viewed, clipped, projected, sorted, clipped triangles
	for (auto &tri : listTriangles) {
	  App::DrawLine (tri.vertices[0].x, tri.vertices[0].y, tri.vertices[1].x, tri.vertices[1].y, 0, 0, 0);
	  App::DrawLine (tri.vertices[1].x, tri.vertices[1].y, tri.vertices[2].x, tri.vertices[2].y, 0, 0, 0);
	  App::DrawLine (tri.vertices[2].x, tri.vertices[2].y, tri.vertices[0].x, tri.vertices[0].y, 0, 0, 0);

	  Graphics3D::DrawTriangle (tri, Color());
	}
  }
}

Vector3 Renderer::PlaneInersection (Vector3 &plane_p, Vector3 &plane_n, Vector3 &lineStart, Vector3 &lineEnd)
{
  plane_n = plane_n.Normalize();
  float plane_d = -(plane_n * plane_p);
  float ad = (lineStart * plane_n);
  float bd = (lineEnd * plane_n);
  float t = (-plane_d - ad) / (bd - ad);
  Vector3 lineStartToEnd = lineEnd - lineStart;
  Vector3 lineToIntersect = lineStartToEnd * t;
  return lineStart + lineToIntersect;
}
int Renderer::GetNumPtsCliped (Vector3 plane_p, Vector3 plane_n, Triangle &in_tri, Triangle &out_tri1, Triangle &out_tri2)
{
  // Make sure plane normal is indeed normal
  plane_n = plane_n.Normalize();

  // Return signed shortest distance from point to plane, plane normal must be normalised
  auto dist = [&] (Vector3 &p) {
	Vector3 n = p.Normalize();
	return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - (plane_n * plane_p));
  };

  // Create two temporary storage arrays to classify points either side of plane
  // If distance sign is positive, point lies on "inside" of plane
  Vector3 *inside_points[3];
  int nInsidePointCount = 0;
  Vector3 *outside_points[3];
  int nOutsidePointCount = 0;

  // Get signed distance of each point in triangle to plane
  float d0 = dist (in_tri.vertices[0]);
  float d1 = dist (in_tri.vertices[1]);
  float d2 = dist (in_tri.vertices[2]);

  if (d0 >= 0) {
	inside_points[nInsidePointCount++] = &in_tri.vertices[0];
  } else {
	outside_points[nOutsidePointCount++] = &in_tri.vertices[0];
  }
  if (d1 >= 0) {
	inside_points[nInsidePointCount++] = &in_tri.vertices[1];
  } else {
	outside_points[nOutsidePointCount++] = &in_tri.vertices[1];
  }
  if (d2 >= 0) {
	inside_points[nInsidePointCount++] = &in_tri.vertices[2];
  } else {
	outside_points[nOutsidePointCount++] = &in_tri.vertices[2];
  }

  // Now classify triangle points, and break the input triangle into
  // smaller output triangles if required. There are four possible
  // outcomes...

  if (nInsidePointCount == 0) {
	// All points lie on the outside of plane, so clip whole triangle
	// It ceases to exist

	return 0; // No returned triangles are valid
  }

  if (nInsidePointCount == 3) {
	// All points lie on the inside of plane, so do nothing
	// and allow the triangle to simply pass through
	out_tri1 = in_tri;

	return 1; // Just the one returned original triangle is valid
  }

  if (nInsidePointCount == 1 && nOutsidePointCount == 2) {
	// Triangle should be clipped. As two points lie outside
	// the plane, the triangle simply becomes a smaller triangle

	// The inside point is valid, so keep that...
	out_tri1.vertices[0] = *inside_points[0];

	// but the two new points are at the locations where the
	// original sides of the triangle (lines) intersect with the plane
	out_tri1.vertices[1] = PlaneInersection (plane_p, plane_n, *inside_points[0], *outside_points[0]);
	out_tri1.vertices[2] = PlaneInersection (plane_p, plane_n, *inside_points[0], *outside_points[1]);

	return 1; // Return the newly formed single triangle
  }

  if (nInsidePointCount == 2 && nOutsidePointCount == 1) {
	// Triangle should be clipped. As two points lie inside the plane,
	// the clipped triangle becomes a "quad". Fortunately, we can
	// represent a quad with two new triangles


	// The first triangle consists of the two inside points and a new
	// point determined by the location where one side of the triangle
	// intersects with the plane
	out_tri1.vertices[0] = *inside_points[0];
	out_tri1.vertices[1] = *inside_points[1];
	out_tri1.vertices[2] = PlaneInersection (plane_p, plane_n, *inside_points[0], *outside_points[0]);

	// The second triangle is composed of one of he inside points, a
	// new point determined by the intersection of the other side of the
	// triangle and the plane, and the newly created point above
	out_tri2.vertices[0] = *inside_points[1];
	out_tri2.vertices[1] = out_tri1.vertices[2];
	out_tri2.vertices[2] = PlaneInersection (plane_p, plane_n, *inside_points[1], *outside_points[0]);

	return 2; // Return two newly formed triangles which form a quad
  }
}

