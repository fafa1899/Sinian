#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

#include <glm/glm.hpp>

namespace Sinian
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspect, float near, float far);		//fov:Camera frustum vertical field of view.
		~PerspectiveCamera();
	};

}


#endif
