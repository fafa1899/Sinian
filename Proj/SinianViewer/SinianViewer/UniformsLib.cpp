#include "UniformsLib.h"

#include <glm/glm.hpp>

namespace Sinian {

UniformsLib& UniformsLib::GetInstance() {
  static UniformsLib instance;
  return instance;
}

UniformsLib::UniformsLib() {
  common.emplace("diffuse", glm::vec3(0.93f, 0.93f, 0.93f));
  common.emplace("opacity", 1.0f);
  common.emplace("map", nullptr); 
}

}  // namespace Sinian
