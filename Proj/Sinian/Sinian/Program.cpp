#include "Program.h"
#include "ProgramParameters.h"
#include "ShaderObject.h"
#include "StlStringExpand.h"
#include "Uniforms.h"

#include <glad/glad.h>

#include <iostream>

using namespace std;

namespace Sinian {

Program::Program(const std::string &cacheKey,
                 std::shared_ptr<ProgramParameters> parameters)
    : cacheKey(cacheKey),
      name(parameters->shaderObject->name),
      usedTimes(1),
      cachedUniforms(nullptr) {
  string &vertexShader = parameters->shaderObject->vertexShader;
  string &fragmentShader = parameters->shaderObject->fragmentShader;

  string prefixVertex;
  string prefixFragment;

  if (false) {
  } else {
    {
      vector<string> prefixVertexTmp;
      prefixVertexTmp.push_back("#define SHADER_NAME " +
                                parameters->shaderObject->name);
	  
      prefixVertexTmp.push_back("uniform mat4 modelMatrix;");
      prefixVertexTmp.push_back("uniform mat4 modelViewMatrix;");
      prefixVertexTmp.push_back("uniform mat4 projectionMatrix;");
      prefixVertexTmp.push_back("uniform mat4 viewMatrix;");
      prefixVertexTmp.push_back("uniform mat3 normalMatrix;");
  	  
      prefixVertex = StlStringExpand::StringJoin(prefixVertexTmp, '\n');    
    }

    {
      prefixFragment =
          "#define SHADER_NAME " + parameters->shaderObject->name + "\n";

      if (parameters->map) {
        prefixFragment = prefixFragment + "#define USE_MAP\n";
      }
    }
  }

  // add version
  {
    prefixVertex = "#version 330 core\n" + prefixVertex;
    prefixFragment = "#version 330 core\n" + prefixFragment;
  }

  // vertexShader = resolveIncludes(vertexShader);
  vertexShader = ReplaceLightNums(vertexShader, parameters);

  // fragmentShader = resolveIncludes(fragmentShader);
  fragmentShader = ReplaceLightNums(fragmentShader, parameters);

  string vertexGlsl = prefixVertex + vertexShader;
  string fragmentGlsl = prefixFragment + fragmentShader;

  //cout << vertexGlsl << endl;

  // shader Program
  program = glCreateProgram();

  // Compile
  GLuint vertex = CompileShader(vertexGlsl, GL_VERTEX_SHADER);
  GLuint fragment = CompileShader(fragmentGlsl, GL_FRAGMENT_SHADER);

  // Link
  glLinkProgram(program);

  // Clean
  CleanShader(vertex);
  CleanShader(fragment);

  CheckProgramErrors(program);
}

Program::~Program() { glDeleteProgram(program); }

std::shared_ptr<Uniforms> Program::GetUniforms() {
  if (!cachedUniforms) {
    cachedUniforms = make_shared<Uniforms>(program);
  }
  return cachedUniforms;
}

string &Program::ReplaceLightNums(
    string &shaderString, std::shared_ptr<ProgramParameters> parameters) {
  return StlStringExpand::ReplaceString(shaderString, "NUM_POINT_LIGHTS",
                                        to_string(parameters->numPointLights));
}

unsigned int Program::CompileShader(string vertexCode,
                                    unsigned int shaderType) {
  const char *vShaderCode = vertexCode.c_str();

  GLuint shaderId = glCreateShader(shaderType);
  glShaderSource(shaderId, 1, &vShaderCode, NULL);
  glCompileShader(shaderId);
  CheckShaderErrors(shaderId);

  glAttachShader(program, shaderId);

  return shaderId;
}

void Program::CheckShaderErrors(unsigned int shader) {
  GLint success;
  GLchar infoLog[1024];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    std::cout << "ERROR::SHADER_COMPILATION_ERROR: "
              << "\n"
              << infoLog
              << "\n -- --------------------------------------------------- -- "
              << std::endl;
  }
}

void Program::CleanShader(unsigned int shaderId) {
  // delete the shaders as they're linked into our program now and no longer
  // necessery
  glDetachShader(program, shaderId);
  glDeleteShader(shaderId);
}

void Program::CheckProgramErrors(unsigned int program) {
  GLint success;
  GLchar infoLog[1024];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 1024, NULL, infoLog);
    std::cout << "ERROR::PROGRAM_LINKING_ERROR : "
              << "\n"
              << infoLog
              << "\n -- --------------------------------------------------- -- "
              << std::endl;
  }
}

}  // namespace Sinian
