#include "Light.h"

namespace Sinian {

Light::Light(glm::vec3 color, float intensity)
    : Object3D(), color(color), intensity(intensity) {
  type = "Light";
}

}  // namespace Sinian
