#include "LightUniforms.h"
#include "Lights/Light.h"

namespace Sinian {

std::map<std::string, UniformSetting>& LightUniforms::Get(
    std::shared_ptr<Light> light) {
  //
  int id = light->Id();
  const auto& lit = lights.find(id);
  if (lit == lights.end()) {
    std::map<std::string, UniformSetting> uniforms;

    if (light->Type() == "PointLight") {
      uniforms.emplace("position", glm::vec3(0.0f, 0.0f, 0.0f));
      uniforms.emplace("color", glm::vec3(0.0f, 0.0f, 0.0f));
      uniforms.emplace("distance", 0);
      uniforms.emplace("decay", 0);
    } else {
      printf("Sinian->LightUniforms->Get Fixed!\n");
    }

    lights[id] = uniforms;
  }

  return lights[id];
}

}  // namespace Sinian