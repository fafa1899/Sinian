#ifndef MESHBASICMATERIAL_H
#define MESHBASICMATERIAL_H

#include "Material.h"

namespace Sinian
{
	class Texture2D;

	class MeshBasicMaterial :
		public Material
	{
	public:
		MeshBasicMaterial();
		virtual ~MeshBasicMaterial();

		void MapTexture(const std::shared_ptr<Sinian::Texture2D> texture);
		inline const std::shared_ptr<Sinian::Texture2D> MapTexture() const { return mapTexture; }

	protected:
		std::shared_ptr<Sinian::Texture2D> mapTexture = nullptr;

		static std::string vertexShaderSource;
		static std::string fragmentShaderSource;
	};
}



#endif

