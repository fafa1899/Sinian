#include "Camera.h"

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace Sinian
{
	Camera::Camera()
		:Object3D(),
		projectionMatrix(1.0f)
	{
	}

	Camera::~Camera()
	{
	}

}








