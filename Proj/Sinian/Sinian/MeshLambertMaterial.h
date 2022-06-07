#ifndef MESHLAMBERTMATERIAL_H
#define MESHLAMBERTMATERIAL_H

#include "Material.h"

namespace Sinian {

class Texture;

class SINIAN_API MeshLambertMaterial : public Material {
 public:
  MeshLambertMaterial();
  // virtual ~MeshLambertMaterial();

  void Color(const glm::vec3& color);
  inline const glm::vec3& Color() { return color; }

  void Map(const std::shared_ptr<Sinian::Texture> texture);
  inline const std::shared_ptr<Sinian::Texture> Map() const { return map; }

 protected:
  std::shared_ptr<Sinian::Texture> map;
  glm::vec3 color;
};

}  // namespace Sinian

#endif
