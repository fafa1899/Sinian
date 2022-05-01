#include "Renderer.h"
#include "mesh.h"

#include <iostream>

using namespace std;

namespace Sinian
{
	static std::shared_ptr<Mesh> Object3DGetMesh(std::shared_ptr<Object3D> object)
	{
		std::shared_ptr<Mesh> mesh = dynamic_pointer_cast<Mesh>(object);
		if (mesh)
		{
			return mesh;
		}
		return nullptr;
	}

	static void Object3DGetMeshs(std::shared_ptr<Object3D> object, vector<shared_ptr<Mesh>>& materials)
	{
		shared_ptr<Mesh> material = Object3DGetMesh(object);
		if (material)
		{
			materials.push_back(material);
		}

		const auto &children = object->Children();
		for (const auto & iter : children)
		{
			Object3DGetMeshs(iter.second, materials);
		}
	}

	void Renderer::SetClearColor(const glm::vec4 & color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::Clear(bool color, bool depth, bool stencil)
	{
		GLbitfield bits = 0;
		if (color) bits |= GL_COLOR_BUFFER_BIT;
		if (depth) bits |= GL_DEPTH_BUFFER_BIT;
		if (stencil) bits |= GL_STENCIL_BUFFER_BIT;
		glClear(bits);
	}

	static void PrintMat(const glm::mat4& m)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("%.9lf\t", m[i][j]);
			}
			printf("\n");
		}
	}

	void Renderer::Render(std::shared_ptr<Object3D> object, std::shared_ptr<Camera> camera)
	{	
		Clear();

		vector<shared_ptr<Mesh>> meshs;
		Object3DGetMeshs(object, meshs);

		//cout << meshs.size() << endl;
		for (size_t mi = 0; mi < meshs.size(); mi++)
		{
			std::map<std::string, std::any> uniforms;
			uniforms.emplace("projection", &(camera->ProjectionMatrix()));
			uniforms.emplace("view", &(camera->ViewMatrix()));
			uniforms.emplace("model", &(meshs[mi]->WorldModelMatrix()));
	
			//PrintMat(meshs[mi]->WorldModelMatrix());
			//cout << endl;

			std::shared_ptr<Material> material = meshs[mi]->MainMaterial();
			material->SetUniforms(uniforms);
			
			material->Update();

			meshs[mi]->Geometry()->Draw();
		}
	}
}


