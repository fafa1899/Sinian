#include "MeshBasicMaterial.h"
#include "Texture2D.h"

#include <string>
#include <iostream>

using namespace std;

namespace Sinian
{
	string MeshBasicMaterial::vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 2) in vec2 aTexCoord;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
		"   TexCoord = aTexCoord;\n"
		"}\n";

	string MeshBasicMaterial::fragmentShaderSource = "#version 330 core\n"
		"in vec2 TexCoord;\n"
		"out vec4 FragColor;\n"		
		"uniform sampler2D mapTexture;\n"			
		"void main()\n"
		"{\n"
		"   //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"   FragColor = texture(mapTexture, TexCoord);\n"
		"}\n";

	MeshBasicMaterial::MeshBasicMaterial() : 
		Material(vertexShaderSource, fragmentShaderSource)
	{	
	}
	
	MeshBasicMaterial::~MeshBasicMaterial()
	{
	}

	void MeshBasicMaterial::MapTexture(const std::shared_ptr<Sinian::Texture2D> texture)
	{
		this->mapTexture = texture;
		SetUniform("mapTexture", texture);
	}
}


