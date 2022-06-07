#ifndef SINGLEUNIFORM_H
#define SINGLEUNIFORM_H

#include "Uniform.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Sinian {

class Texture;

class SingleUniform : public Uniform {
 public:
  SingleUniform(const std::string& id, GLint addr, GLenum type)
      : Uniform(id), addr(addr), type(type) {
    className = "SingleUniform";
  }

  void SetValue(const std::any& v,
                std::shared_ptr<Textures> textures = nullptr);

  std::any cache;

 private:
  void SetValueV1f(const float& v);
  void SetValueV3f(const glm::vec3& v);
  void SetValueM3(const glm::mat3& v);
  void SetValueM4(const glm::mat4& v);
  void SetValueT1(std::shared_ptr<Texture> v,
                  std::shared_ptr<Textures> textures);

  GLint addr;
  GLenum type;
};

}  // namespace Sinian

#endif
