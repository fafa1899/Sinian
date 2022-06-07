#ifndef SINIAN_LIGHTS_H
#define SINIAN_LIGHTS_H

#include "LightUniforms.h"
#include "LightState.h"

#include <memory>
#include <vector>
#include <string>

namespace Sinian {

class Light;
class Camera;

class Lights {
 public:
  Lights();

  void Setup(const std::vector<std::shared_ptr<Light>>& lightsArray,
             std::shared_ptr<Camera> camera);

  inline const LightState& State() const { return state; }

 private:
  int nextVersion;

  std::unique_ptr<LightUniforms> cache;
  LightState state;
};

}  // namespace Sinian

#endif
