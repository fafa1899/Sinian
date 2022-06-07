#include "SingleUniform.h"
#include "Texture.h"
#include "Textures.h"

#include <iostream>

using namespace std;

namespace Sinian {

void SingleUniform::SetValue(const std::any& v,
                             std::shared_ptr<Textures> textures) {
  switch (type) {
    case GL_FLOAT: {
      SetValueV1f(std::any_cast<float>(v));
      break;
    }
    case GL_FLOAT_VEC3: {
      SetValueV3f(std::any_cast<glm::vec3>(v));
      break;
    }
    case GL_FLOAT_MAT3: {
      SetValueM3(std::any_cast<glm::mat3>(v));
      break;
    }
    case GL_FLOAT_MAT4: {
      SetValueM4(std::any_cast<glm::mat4>(v));
      break;
    }
    case GL_SAMPLER_2D: {
      SetValueT1(std::any_cast<std::shared_ptr<Texture>>(v), textures);
      break;
    }
    default: {
      printf("No Support Uniform Type : %d!\n", type);
      break;
    }
  }
}

void SingleUniform::SetValueT1(std::shared_ptr<Texture> v,
                               std::shared_ptr<Textures> textures) {
  int unit = textures->AllocateTextureUnit();
  
  if (!cache.has_value() || std::any_cast<int>(cache) != unit) {
    glUniform1i(addr, unit);
    cache = unit;
  }

  textures->SetTexture2D(v, unit);
}

void SingleUniform::SetValueV1f(const float& v) {
  if (cache.has_value() && std::any_cast<float>(cache) == v) {
    return;
  }

  glUniform1f(addr, v);
  cache = v;
}

void SingleUniform::SetValueV3f(const glm::vec3& v) {
  if (cache.has_value() && std::any_cast<glm::vec3>(cache) == v) {
    return;
  }

  glUniform3fv(addr, 1, &v[0]);
  cache = v;
}

void SingleUniform::SetValueM3(const glm::mat3& v) { 
  if (cache.has_value() && std::any_cast<glm::mat3>(cache) == v) {
    return;
  }

  glUniformMatrix3fv(addr, 1, GL_FALSE, &(v[0][0]));
  cache = v;
}

void SingleUniform::SetValueM4(const glm::mat4& v) {
  if (cache.has_value() && std::any_cast<glm::mat4>(cache) == v) {
    return;
  }

  glUniformMatrix4fv(addr, 1, GL_FALSE, &(v[0][0]));
  cache = v;
}

}  // namespace Sinian