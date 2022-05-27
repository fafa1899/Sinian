#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

namespace Sinian
{
	Shader::~Shader()
	{
		glDeleteProgram(ID);
	}

	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		// shader Program
		ID = glCreateProgram();

		//Compile
		GLuint vertex = CompileShaderFromFile(vertexPath, GL_VERTEX_SHADER);
		GLuint fragment = CompileShaderFromFile(fragmentPath, GL_FRAGMENT_SHADER);
	
		//Link
		glLinkProgram(ID);

		//Clean
		CleanShader(vertex);
		CleanShader(fragment);
	
		CheckProgramErrors(ID);
	}

	Shader::Shader(const string &vertexShaderSource, const string &fragmentShaderSource)
	{
		// shader Program
		ID = glCreateProgram();

		//Compile
		GLuint vertex = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
		GLuint fragment = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

		//Link
		glLinkProgram(ID);

		//Clean
		CleanShader(vertex);
		CleanShader(fragment);

		CheckProgramErrors(ID);
	}

	void Shader::ReadShaderFile(string shaderPath, std::string& shaderCode)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::ifstream vShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			vShaderFile.open(shaderPath);

			std::stringstream vShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();

			// close file handlers
			vShaderFile.close();

			// convert stream into string
			shaderCode = vShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		}
	}

	GLuint Shader::CompileShader(string vertexCode, GLenum shaderType)
	{
		const char* vShaderCode = vertexCode.c_str();

		GLuint shaderId = glCreateShader(shaderType);
		glShaderSource(shaderId, 1, &vShaderCode, NULL);
		glCompileShader(shaderId);
		CheckShaderErrors(shaderId);

		glAttachShader(ID, shaderId);

		return shaderId;
	}

	void Shader::CleanShader(GLuint shaderId)
	{
		// delete the shaders as they're linked into our program now and no longer necessery
		glDetachShader(ID, shaderId);
		glDeleteShader(shaderId);
	}

	GLuint Shader::CompileShaderFromFile(const char* shaderPath, GLenum shaderType)
	{
		std::string vertexCode;
		ReadShaderFile(shaderPath, vertexCode);
		return CompileShader(vertexCode, shaderType);
	}

	void Shader::CheckShaderErrors(GLuint shader)
	{
		GLint success;
		GLchar infoLog[1024];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}

	void Shader::CheckProgramErrors(GLuint program)
	{
		GLint success;
		GLchar infoLog[1024];
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR : " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}

	void Shader::SetUniform(const std::string &name, std::any value)
	{
		const auto& valueType = value.type();	
		if (valueType == typeid(int))
		{				
			glUniform1i(glGetUniformLocation(ID, name.c_str()), std::any_cast<int>(value));
		}
		else if (valueType == typeid(glm::vec3 const *))
		{
			glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1,
				reinterpret_cast<float const*>(std::any_cast<glm::vec3 const *>(value)));				
		}
		else if (valueType == typeid(glm::mat4 const * ))
		{		
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
				reinterpret_cast<float const*>(std::any_cast<glm::mat4 const *>(value)));
		}		
	}

	void Shader::Use() const
	{
		glUseProgram(ID);		
	}
}