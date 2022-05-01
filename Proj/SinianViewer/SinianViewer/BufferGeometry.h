#ifndef BUFFERGEOMETRY_H
#define BUFFERGEOMETRY_H

#include "Geometry.h"

#include <vector>

namespace Sinian
{
	#define MAX_BONE_INFLUENCE 4

	struct Vertex
	{
		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
		//bone indexes which will influence this vertex
		int m_BoneIDs[MAX_BONE_INFLUENCE];
		//weights from each bone
		float m_Weights[MAX_BONE_INFLUENCE];
	};

	class BufferGeometry : public Geometry
	{
	public:
		BufferGeometry();
		virtual ~BufferGeometry();
		
		void SetAttribute(const std::vector<Vertex>& vertices);
		void SetIndex(const std::vector<unsigned int>& indices);

		void Draw();

	protected:		
		size_t verticeNum = 0;
		size_t indexNum = 0;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		unsigned int VAO;
		unsigned int VBO, EBO;
	};
}
#endif

