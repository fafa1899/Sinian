#include "BoxGeometry.h"

#include <vector>

using namespace std;

namespace Sinian
{
	BoxGeometry::BoxGeometry(double width, double height, double depth) :
		BufferGeometry()
	{		
		float extentX = static_cast<float>(width / 2.0);
		float extentY = static_cast<float>(height / 2.0);
		float extentZ = static_cast<float>(depth / 2.0);

		float verticesTmp[] = {
			extentX,  extentY, -extentZ,  1.0f, 1.0f,
			extentX, -extentY, -extentZ,  1.0f, 0.0f,
			-extentX, -extentY, -extentZ,  0.0f, 0.0f,
			-extentX, -extentY, -extentZ,  0.0f, 0.0f,
			-extentX,  extentY, -extentZ,  0.0f, 1.0f,
			extentX,  extentY, -extentZ,  1.0f, 1.0f,

			-extentX, -extentY,  extentZ,  0.0f, 0.0f,
			 extentX, -extentY,  extentZ,  1.0f, 0.0f,
			 extentX,  extentY,  extentZ,  1.0f, 1.0f,
			 extentX,  extentY,  extentZ,  1.0f, 1.0f,
			-extentX,  extentY,  extentZ,  0.0f, 1.0f,
			-extentX, -extentY,  extentZ,  0.0f, 0.0f,

			-extentX,  extentY,  extentZ,  1.0f, 0.0f,
			-extentX,  extentY, -extentZ,  1.0f, 1.0f,
			-extentX, -extentY, -extentZ,  0.0f, 1.0f,
			-extentX, -extentY, -extentZ,  0.0f, 1.0f,
			-extentX, -extentY,  extentZ,  0.0f, 0.0f,
			-extentX,  extentY,  extentZ,  1.0f, 0.0f,

			 extentX, -extentY, -extentZ,  0.0f, 1.0f,
			 extentX,  extentY, -extentZ,  1.0f, 1.0f,
			 extentX,  extentY,  extentZ,  1.0f, 0.0f,
			 extentX,  extentY,  extentZ,  1.0f, 0.0f,
			 extentX, -extentY,  extentZ,  0.0f, 0.0f,
			 extentX, -extentY, -extentZ,  0.0f, 1.0f,

			-extentX, -extentY, -extentZ,  0.0f, 1.0f,
			 extentX, -extentY, -extentZ,  1.0f, 1.0f,
			 extentX, -extentY,  extentZ,  1.0f, 0.0f,
			 extentX, -extentY,  extentZ,  1.0f, 0.0f,
			-extentX, -extentY,  extentZ,  0.0f, 0.0f,
			-extentX, -extentY, -extentZ,  0.0f, 1.0f,

			 extentX,  extentY,  extentZ,  1.0f, 0.0f,
			 extentX,  extentY, -extentZ,  1.0f, 1.0f,
			-extentX,  extentY, -extentZ,  0.0f, 1.0f,
			-extentX,  extentY, -extentZ,  0.0f, 1.0f,
			-extentX,  extentY,  extentZ,  0.0f, 0.0f,
			extentX,  extentY,  extentZ,  1.0f, 0.0f,
		};
		
		vector<Vertex> vertices(36);
		for (size_t vi = 0; vi < vertices.size(); vi++)
		{
			vertices[vi].Position = glm::vec3(verticesTmp[vi * 5], verticesTmp[vi * 5 + 1], verticesTmp[vi * 5 + 2]);
			vertices[vi].TexCoords = glm::vec2(verticesTmp[vi * 5 + 3], verticesTmp[vi * 5 + 4]);
		}
				
		SetAttribute(vertices);	
	}
}