#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"
#include "SinianApi.h"

#include <glm/glm.hpp>

namespace Sinian {

class SINIAN_API PerspectiveCamera : public Camera {
 public:
  PerspectiveCamera(float fov, float aspect, float near,
                    float far);  // fov:Camera frustum vertical field of view.
  ~PerspectiveCamera();

  void Aspect(const float& aspect);

 private:
  float fov;
  float aspect;
  float near;
  float far;
};

}  // namespace Sinian

#endif
