#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include <map>

#include "Shader.h"
#include "RenderState.h"

namespace Sinian
{
	class Texture2D;

	class Material
	{
	public:
		Material(const char* vertexPath, const char* fragmentPath);
		Material(const std::string &vertexShaderSource, const std::string &fragmentShaderSourc);
		virtual ~Material();

		void Update();
	
		const std::vector<std::shared_ptr<Texture2D>> & Textures() const { return textures; }

		void SetUniform(const std::string &name, std::any value);
		void SetUniforms(const std::map<std::string, std::any>& uniforms);
		
		const bool & DepthTest() { return renderState.depthTest.enabled; }
		void DepthTest(const bool & enabled) { renderState.depthTest.enabled = enabled; }

		const GLenum &DepthFunc() { return renderState.depthTest.func; }
		void DepthFunc(const GLenum & func) { renderState.depthTest.func = func; }

		const bool & CullEnabled() { return renderState.cull.enabled; }
		void CullEnabled(const bool & enabled) { renderState.cull.enabled = enabled; }
				
	protected:
		void SetUniformValue(const std::string &name, std::any value);

		Shader shader;

		std::map<std::string, int> textureNameAndTextureUnit;
		std::vector<std::shared_ptr<Texture2D>> textures;	

		RenderState renderState;
	};
}

#endif
