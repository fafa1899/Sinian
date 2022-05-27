#include "PerspectiveCamera.h"

#include <iostream>
#include <typeinfo>

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

namespace Sinian {
PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near,
                                     float far)
    : Camera(), fov(fov), aspect(aspect), near(near), far(far) {
  projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}

PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::Aspect(const float& aspect) {
  this->aspect = aspect;
  projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}

}  // namespace Sinian
