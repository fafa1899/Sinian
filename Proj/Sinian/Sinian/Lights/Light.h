#ifndef SINIAN_LIGHT_H
#define SINIAN_LIGHT_H

#include "../Object3D.h"

namespace Sinian {

class SINIAN_API Light : public Object3D {
 public:
  Light(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);

  inline const glm::vec3& Color() const { return color; }

  inline const float& Intensity() const { return intensity; }

 protected:
  glm::vec3 color;
  float intensity;
};

}  // namespace Sinian

#endif
