#ifndef LIGHTSTATE_H
#define LIGHTSTATE_H

#include "UniformSetting.h"

#include <glm/vec3.hpp>

#include <map>
#include <string>
#include <vector>

namespace Sinian {

struct LightStateHash {
  int pointLength = -1;
};

struct LightState {
  LightState() : version(0), ambient(0.0f, 0.0f, 0.0f) {}

  int version;

  LightStateHash hash;

  glm::vec3 ambient;
  std::vector<std::map<std::string, UniformSetting>> point;
};

}  // namespace Sinian

#endif