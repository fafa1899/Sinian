#include "PointLight.h"

namespace Sinian
{
	PointLight::PointLight(glm::vec3 color, float intensity, float distance, float decay):
		Light(color, intensity),
		distance(distance),
		decay(decay)
	{
	}
}
