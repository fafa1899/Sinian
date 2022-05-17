#ifndef SINIAN_MESH_H
#define SINIAN_MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include <map>
#include <any>

#include "shader.h"
#include "Texture2D.h"
#include "BufferGeometry.h"
#include "Material.h"
#include "Object3D.h"

namespace Sinian
{
	//struct Texture
	//{
	//	unsigned int id;
	//	std::string type;
	//	std::string path;
	//};

	class Mesh : public Object3D
	{
	public:
		Mesh(std::shared_ptr<BufferGeometry> geometry, std::shared_ptr<Material> material);
		virtual ~Mesh();

		const std::shared_ptr<Material> MainMaterial() const { return material; }
		const std::shared_ptr<BufferGeometry> Geometry() const { return geometry; }

		// render the mesh
		void Draw();

	protected:
		std::shared_ptr<BufferGeometry> geometry;
		std::shared_ptr<Material> material;
	};
}
#endif
