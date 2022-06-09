#ifndef SHADERMATERIAL_H
#define SHADERMATERIAL_H

#include "Material.h"

namespace Sinian
{
	class ShaderMaterial :
		public Material
	{
	public:
		ShaderMaterial(const std::string & vertexShader, const std::string & fragmentShader,
			const std::map<std::string, std::any>& uniforms);

		ShaderMaterial(const char* vertexPath, const char* fragmentPath, const std::map<std::string, std::any>& uniforms);
			
		virtual ~ShaderMaterial();
	};
}

#endif

