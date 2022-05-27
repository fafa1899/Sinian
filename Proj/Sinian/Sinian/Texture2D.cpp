#include "Texture2D.h"
//#include "stb_image.h"

#include <string>

#include <glad/glad.h> // holds all OpenGL type declarations

using namespace std;

namespace Sinian
{
	Texture2D::Texture2D(const char *path)
	{		
		glGenTextures(1, &id);	
		TextureFromFile(path);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &id);
	}

	Texture2D::Texture2D(const Texture2D &t)
	{		
		this->id = t.id;
	}

	Texture2D &Texture2D::operator=(const Texture2D &t)
	{
		if (this == &t)
		{
			return *this;
		}
			
		this->id = t.id;

		return *this;
	}

	void Texture2D::TextureFromFile(const char *path)
	{	
		/*
		//tell stb_image.h to flip loaded texture's on the y-axis.
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);			
		}
		else
		{
			printf("Texture failed to load at path: %s\n", path);			
		}

		stbi_image_free(data); */
	}

}






