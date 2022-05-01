#include "PerspectiveCamera.h"

#include <iostream>
#include <typeinfo> 

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

namespace Sinian
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
		:Camera()		
	{
		projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);		
	}

	PerspectiveCamera::~PerspectiveCamera()
	{
	}
}


