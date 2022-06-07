#include "Lights.h"
#include "Camera.h"
#include "Lights/Light.h"
#include "Lights/PointLight.h"

using namespace std;

namespace Sinian {

Lights::Lights() : nextVersion(0), cache(make_unique<LightUniforms>()) {}

// Todo£ºIt may not be necessary to use a caching mechanism.The map
// container uses subscripting, and std::any.
void Lights::Setup(const std::vector<std::shared_ptr<Light>>& lightsArray,
                   std::shared_ptr<Camera> camera) {
  //
  float r = 0, g = 0, b = 0;

  int directionalLength = 0;
  int pointLength = 0;
  int spotLength = 0;
  int rectAreaLength = 0;
  int hemiLength = 0;

  int numDirectionalShadows = 0;
  int numPointShadows = 0;
  int numSpotShadows = 0;

  for (size_t i = 0, l = lightsArray.size(); i < l; i++) {
    const auto& light = lightsArray[i];
    const auto& typeName = light->Type();

    const auto& color = light->Color();
    const auto& intensity = light->Intensity();
    // var distance = light.distance;

    const glm::mat4& viewMatrix = camera->ViewMatrix();

	if (typeName == "AmbientLight") {
      r += color.r * intensity;
      g += color.g * intensity;
      b += color.b * intensity;
    }
    else if (typeName == "PointLight") {
      shared_ptr<PointLight> pointLight =
          static_pointer_cast<PointLight>(light);

      auto& uniforms = cache->Get(light);

      glm::vec4 viewCoord = viewMatrix * glm::vec4(light->WorldPosition(), 1);
      uniforms["position"].value =
          glm::vec3(viewCoord.x / viewCoord.w, viewCoord.y / viewCoord.w,
                    viewCoord.z / viewCoord.w);

      uniforms["color"].value = pointLight->Color() * pointLight->Intensity();
      uniforms["distance"].value = pointLight->Distance();
      uniforms["decay"].value = pointLight->Decay();

      if (pointLength < state.point.size()) {
        state.point[pointLength] = uniforms;
      } else {
        state.point.push_back(uniforms);
      }

      pointLength++;
    }
  }

  state.ambient[0] = r;
  state.ambient[1] = g;
  state.ambient[2] = b;

  LightStateHash& hash = state.hash;
  if (hash.pointLength != pointLength) {
    hash.pointLength = pointLength;
    state.version = nextVersion++;
  }
}

}  // namespace Sinian