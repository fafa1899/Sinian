#include "RenderState.h"

namespace Sinian
{
	RenderState::RenderState()
	{
		// configure global opengl state
// -----------------------------
	//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);
	}
	   
	void RenderState::EnableOrDisable(GLenum glEnum, bool enable)
	{
		if (enable)
		{
			glEnable(glEnum);
		}
		else
		{
			glDisable(glEnum);
		}
	}

	void RenderState::Apply()
	{
		ApplyCull();
		ApplyDepthTest();
	}

	void RenderState::ApplyDepthTest()
	{
		EnableOrDisable(GL_DEPTH_TEST, depthTest.enabled);
		if (depthTest.enabled) 
		{
			glDepthFunc(depthTest.func);
		}
	}

	void RenderState::ApplyCull()
	{
		EnableOrDisable(GL_CULL_FACE, cull.enabled);
		if (cull.enabled)
		{
			glCullFace(cull.face);
		}
	}
}
