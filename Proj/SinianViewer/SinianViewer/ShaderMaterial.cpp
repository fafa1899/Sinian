#include "ShaderMaterial.h"

namespace Sinian
{
	ShaderMaterial::ShaderMaterial(const std::string & vertexShader, const std::string & fragmentShader, 
		const std::map<std::string, std::any>& uniforms):
		Material(vertexShader, fragmentShader)
	{		
		SetUniforms(uniforms);
	}

	ShaderMaterial::ShaderMaterial(const char* vertexPath, const char* fragmentPath, const std::map<std::string, std::any>& uniforms)
		:Material(vertexPath, fragmentPath)
	{
		SetUniforms(uniforms);
	}

	ShaderMaterial::~ShaderMaterial()
	{

	}
}