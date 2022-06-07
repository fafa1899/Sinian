#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

namespace Sinian {

class SINIAN_API PointLight : public Light {
 public:
  PointLight(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
             float intensity = 1.0f, float distance = 0.0f, float decay = 1.0f);

  inline const float& Distance() const { return distance; }

  inline const float& Decay() const { return decay; }
  
 protected:
  float distance;
  float decay;
};

}  // namespace Sinian

#endif
