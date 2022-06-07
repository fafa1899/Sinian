#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "Light.h"

namespace Sinian {

class SINIAN_API AmbientLight : public Light {
 public:
  AmbientLight(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
               float intensity = 1.0f);
};

}  // namespace Sinian

#endif