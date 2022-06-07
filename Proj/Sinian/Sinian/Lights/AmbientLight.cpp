#include "AmbientLight.h"

namespace Sinian {

AmbientLight::AmbientLight(glm::vec3 color, float intensity)
    : Light(color, intensity) {
  type = "AmbientLight";
}

}  // namespace Sinian