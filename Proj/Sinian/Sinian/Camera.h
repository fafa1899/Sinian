#ifndef CAMERA_H
#define CAMERA_H

#include "Object3D.h"

#include <glm/glm.hpp>

namespace Sinian {

// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class SINIAN_API Camera : public Object3D {
 public:
  Camera();
  virtual ~Camera();

  // returns the view matrix
  const glm::mat4 &ViewMatrix() const { return worldModelMatrixInverse; }

  const glm::mat4 &ProjectionMatrix() const { return projectionMatrix; }

 protected:
  glm::mat4 projectionMatrix;
};

}  // namespace Sinian

#endif
