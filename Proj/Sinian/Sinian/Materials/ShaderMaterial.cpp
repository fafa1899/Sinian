#include "ShaderMaterial.h"

namespace Sinian
{
	ShaderMaterial::ShaderMaterial(const std::string & vertexShader, const std::string & fragmentShader, 
		const std::map<std::string, std::any>& uniforms):
		Material()
	{		
		type = "ShaderMaterial";

		//SetUniforms(uniforms);
	}

	ShaderMaterial::ShaderMaterial(const char* vertexPath, const char* fragmentPath, const std::map<std::string, std::any>& uniforms)
		:Material()
	{
		//SetUniforms(uniforms);
	}

	ShaderMaterial::~ShaderMaterial()
	{

	}
}