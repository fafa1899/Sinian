#pragma once
#include <glad/glad.h>

namespace Sinian
{
	class RenderState
	{
		struct DepthTest
		{
			bool enabled = true;
			GLenum func = GL_LESS;
		};

		struct Cull
		{
			bool enabled = true;
			GLenum face = GL_BACK;
		};

	public:
		RenderState();

		void Apply();

		DepthTest depthTest;
		Cull cull;

	protected:
		void EnableOrDisable(GLenum glEnum, bool enable);

		void ApplyDepthTest();
		void ApplyCull();
	};
}



