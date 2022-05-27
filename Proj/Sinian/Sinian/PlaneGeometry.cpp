#include "PlaneGeometry.h"

using namespace std;

namespace Sinian
{
	PlaneGeometry::PlaneGeometry(double width, double height):
		BufferGeometry()
	{
		float extentX = static_cast<float>(width / 2.0);
		float extentY = static_cast<float>(height / 2.0);

		vector<Vertex> vertices(4);
		{
			vertices[0].Position = glm::vec3(extentX, extentY, 0.0f);
			vertices[1].Position = glm::vec3(extentX, -extentY, 0.0f);
			vertices[2].Position = glm::vec3(-extentX, -extentY, 0.0f);
			vertices[3].Position = glm::vec3(-extentX, extentY, 0.0f);

			vertices[0].TexCoords = glm::vec2(1.0f, 1.0f);
			vertices[1].TexCoords = glm::vec2(1.0f, 0.0f);
			vertices[2].TexCoords = glm::vec2(0.0f, 0.0f);
			vertices[3].TexCoords = glm::vec2(0.0f, 1.0f);
		}

		vector<unsigned int> indices;
		{
			indices = { 3, 1, 0, 3, 2, 1 };
		}

		SetAttribute(vertices);
		SetIndex(indices);
	}
}

