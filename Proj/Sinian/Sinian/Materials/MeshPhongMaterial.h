#ifndef MESHPHONGMATERIAL_H
#define MESHPHONGMATERIAL_H

#include "Material.h"

namespace Sinian {

class Texture;

class SINIAN_API MeshPhongMaterial : public Material {
 public:
  MeshPhongMaterial();

  inline const glm::vec3& Color() { return color; }
  void Color(const glm::vec3& color);

  inline const glm::vec3& Specular() { return specular; }
  void Specular(const glm::vec3& specular) { this->specular = specular; }

  inline const float& Shininess() { return shininess; }
  void Shininess(const float& shininess) { this->shininess = shininess; }

  inline const std::shared_ptr<Sinian::Texture> Map() const { return map; }
  void Map(const std::shared_ptr<Sinian::Texture> texture);

  inline const std::shared_ptr<Sinian::Texture>& SpecularMap() {
    return specularMap;
  }
  void SpecularMap(const std::shared_ptr<Sinian::Texture>& specularMap) {
    this->specularMap = specularMap;
  }

 private:
  glm::vec3 color;
  glm::vec3 specular;
  float shininess;
  std::shared_ptr<Sinian::Texture> map;

  std::shared_ptr<Sinian::Texture> specularMap;
};

}  // namespace Sinian

#endif
