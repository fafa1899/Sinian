#include "MeshBasicMaterial.h"
#include "Texture.h"

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
		"uniform vec3 diffuse;\n"
		"const float opacity = 1.0f;\n"
		"#ifdef USE_MAP\n"
		"uniform sampler2D map;\n"
		"#endif\n"
		"//uniform sampler2D mapTexture;\n"			
		"void main()\n"
		"{\n"
		"   //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"   //FragColor = texture(mapTexture, TexCoord);\n"
		"	vec4 diffuseColor = vec4( diffuse, opacity );\n"
		"//#ifdef USE_MAP\n"
		"	//vec4 texelColor = texture2D(map, vUv);\n"
		"   //texelColor = mapTexelToLinear(texelColor);\n"
		"	//diffuseColor *= texelColor;\n"
		"//#endif\n"	
		"	gl_FragColor = diffuseColor;\n"	
		"}\n";

	MeshBasicMaterial::MeshBasicMaterial() : 
		Material(),		
		map(nullptr),
		color(1.0f, 1.0f, 1.0f)
	{	
		type = "MeshBasicMaterial";
	}
	
	MeshBasicMaterial::~MeshBasicMaterial()
	{
	}

	void MeshBasicMaterial::Color(const glm::vec3& color)
	{
		this->color = color;
		//SetUniform("diffuse", &color);
	}

	void MeshBasicMaterial::Map(const std::shared_ptr<Sinian::Texture> texture)
	{
		this->map = texture;
		//SetUniform("map", texture);
	}
}


