#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

namespace Sinian
{
	class PointLight:
		public Light
	{
	public:
		PointLight(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f, float distance = 0.0f, float decay = 1.0f);

	protected:
		float distance;
		float	decay;
	};
}

#endif

