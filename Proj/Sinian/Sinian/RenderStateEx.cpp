#include "RenderStateEx.h"

using namespace std;

namespace Sinian {

RenderStateEx::RenderStateEx(){}

void RenderStateEx::Init() {
  lightsArray.clear();
  shadowsArray.clear();
}

void RenderStateEx::PushLight(std::shared_ptr<Light> light) {
  lightsArray.push_back(light);
}

void RenderStateEx::SetupLights(shared_ptr<Camera> camera) {
  lights.Setup(lightsArray, camera);
}

}  // namespace Sinian
