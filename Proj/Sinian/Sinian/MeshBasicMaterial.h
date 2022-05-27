#ifndef MESHBASICMATERIAL_H
#define MESHBASICMATERIAL_H

#include "Material.h"

namespace Sinian
{
	class Texture;

	class SINIAN_API MeshBasicMaterial :
		public Material
	{
	public:
		MeshBasicMaterial();
		virtual ~MeshBasicMaterial();

		void Color(const glm::vec3& color);
		inline const glm::vec3& Color() { return color; }

		void Map(const std::shared_ptr<Sinian::Texture> texture);
		inline const std::shared_ptr<Sinian::Texture> Map() const { return map; }


	protected:
		std::shared_ptr<Sinian::Texture> map;
		glm::vec3 color;

		static std::string vertexShaderSource;
		static std::string fragmentShaderSource;
	};
}



#endif

