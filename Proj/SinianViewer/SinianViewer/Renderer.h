#ifndef RENDERER_H
#define RENDERER_H

#include "Object3D.h"
#include "Camera.h"

#include <memory>

namespace Sinian
{
	class Renderer
	{
	public:
		void SetClearColor(const glm::vec4 & color );

		void Clear(bool color = true, bool depth = true, bool stencil = true);
		void ClearColor(){ Clear(true, false, false); }
		void ClearDepth() { Clear(false, true, false); }
		void ClearStencil() { Clear(false, false, true); }

		void Render(std::shared_ptr<Object3D> object, std::shared_ptr<Camera> camera);		
	};
}

#endif