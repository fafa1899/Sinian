#include "MeshLambertMaterial.h"

namespace Sinian {

MeshLambertMaterial::MeshLambertMaterial()
    : Material(), map(nullptr), color(1.0f, 1.0f, 1.0f) {
  type = "MeshLambertMaterial";
}

void MeshLambertMaterial::Color(const glm::vec3& color) { this->color = color; }

void MeshLambertMaterial::Map(const std::shared_ptr<Sinian::Texture> texture) {
  this->map = texture;
}

}  // namespace Sinian