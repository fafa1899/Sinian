#include "MeshBasicMaterial.h"
#include "../Texture.h"

#include <string>
#include <iostream>

using namespace std;

namespace Sinian
{
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


