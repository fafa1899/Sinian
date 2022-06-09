#ifndef MESHBASICMATERIAL_H
#define MESHBASICMATERIAL_H

#include "Material.h"

namespace Sinian {
class Texture;

class SINIAN_API MeshBasicMaterial : public Material {
 public:
  MeshBasicMaterial();
  virtual ~MeshBasicMaterial();

  void Color(const glm::vec3& color);
  inline const glm::vec3& Color() { return color; }

  void Map(const std::shared_ptr<Sinian::Texture> texture);
  inline const std::shared_ptr<Sinian::Texture> Map() const { return map; }

  inline const std::shared_ptr<Sinian::Texture>& SpecularMap() {
    return specularMap;
  }
  void SpecularMap(const std::shared_ptr<Sinian::Texture>& specularMap) {
    this->specularMap = specularMap;
  }

 protected:
  std::shared_ptr<Sinian::Texture> map;
  glm::vec3 color;

  std::shared_ptr<Sinian::Texture> specularMap;
};
}  // namespace Sinian

#endif
