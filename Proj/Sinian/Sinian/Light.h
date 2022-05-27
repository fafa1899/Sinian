#ifndef LIGHT_H
#define LIGHT_H

#include "Object3D.h"

namespace Sinian
{
	class Light :
		public Object3D
	{
	public:
		Light(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);

	protected:
		glm::vec3 color;
		float intensity;
	};
}

#endif


