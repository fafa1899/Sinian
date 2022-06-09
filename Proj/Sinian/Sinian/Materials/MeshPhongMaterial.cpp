#include "MeshPhongMaterial.h"

namespace Sinian {

MeshPhongMaterial::MeshPhongMaterial()
    : Material(),
      color(1.0f, 1.0f, 1.0f),
      specular(0.066667f, 0.066667f, 0.066667f),
      shininess(30.0f),
      map(nullptr),
      specularMap(nullptr) {
  type = "MeshPhongMaterial";
}

void MeshPhongMaterial::Color(const glm::vec3& color) { this->color = color; }

void MeshPhongMaterial::Map(const std::shared_ptr<Sinian::Texture> texture) {
  this->map = texture;
}

}  // namespace Sinian