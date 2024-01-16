#include "stdafx.h"
#include "Camera.h"

Camera Camera::mainCamera = Camera();

Camera::Camera() : 
	pos (Vector3()), 
	target (Vector3 ({0, 0, 1})), 
	up (Vector3 ({0, 1, 0})), 
	fXaw (0.0f), fYaw (0.0f), fZaw (0.0f)
{
}

