#include "stdafx.h"
#include "Camera.h"

Camera Camera::mainCamera = Camera();

Camera::Camera() : 
	target (Vector3 ({0, 0, 1}))
{
}

