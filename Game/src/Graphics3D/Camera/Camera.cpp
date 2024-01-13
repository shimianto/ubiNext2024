#include "stdafx.h"
#include "Camera.h"

Camera Camera::mainCamera = Camera();

Camera::Camera() : 
	pos (Vector3()), 
	target (Vector3 ({0, 0, 1})), 
	up (Vector3 ({0, 1, 0}))
{
}

void Camera::UpdateViewMatrices()
{
  // Calculate new forward direction
  Vector3 vForward = (target - pos).Normalize();
  // Calculate new right direction
  Vector3 vRight = Vector3::CrossProduct (vForward, up).Normalize();
  // Calculate new Up direction
  Vector3 vUp = Vector3::CrossProduct (vRight, vForward);


  // Construct View Matrix based on Camera
  viewMat.m[0][0] = vRight.x;
  viewMat.m[0][1] = vRight.y;
  viewMat.m[0][2] = vRight.z;
  viewMat.m[0][3] = 0.0f;
  viewMat.m[1][0] = vUp.x;
  viewMat.m[1][1] = vUp.y;
  viewMat.m[1][2] = vUp.z;
  viewMat.m[1][3] = 0.0f;
  viewMat.m[2][0] = vForward.x;
  viewMat.m[2][1] = vForward.y;
  viewMat.m[2][2] = vForward.z;
  viewMat.m[2][3] = 0.0f;
  viewMat.m[3][0] = pos.x;
  viewMat.m[3][1] = pos.y;
  viewMat.m[3][2] = pos.z;
  viewMat.m[3][3] = 1.0f;

  // Invert View Matrix
  invViewMat.m[0][0] = vRight.x;
  invViewMat.m[0][1] = vUp.x;
  invViewMat.m[0][2] = vForward.x;
  invViewMat.m[0][3] = 0.0f;
  invViewMat.m[1][0] = vRight.y;
  invViewMat.m[1][1] = vUp.y;
  invViewMat.m[1][2] = vForward.y;
  invViewMat.m[1][3] = 0.0f;
  invViewMat.m[2][0] = vRight.z;
  invViewMat.m[2][1] = vUp.z;
  invViewMat.m[2][2] = vForward.z;
  invViewMat.m[2][3] = 0.0f;
  invViewMat.m[3][0] = -(vRight * pos);
  invViewMat.m[3][1] = -(vUp * pos);
  invViewMat.m[3][2] = -(vForward * pos);
}

Matrix Camera::GetViewMatrix() const
{
  return viewMat;
}

Matrix Camera::GetInvViewMatrix() const
{
  return invViewMat;
}

