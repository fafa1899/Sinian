#ifndef SINIAN_RENDERSTATEEX_H
#define SINIAN_RENDERSTATEEx_H

#include "Lights/Light.h"
#include "Lights.h"

#include <memory>
#include <vector>

namespace Sinian {

class Camera;
class Lights;

class RenderStateEx {
 public:
  RenderStateEx();

  void Init();

  void PushLight(std::shared_ptr<Light> light);

  void SetupLights(std::shared_ptr<Camera> camera);

  inline const Lights& GetLights() const { return lights; }

 private:
  Lights lights;

  std::vector<std::shared_ptr<Light>> lightsArray;
  std::vector<std::shared_ptr<Light>> shadowsArray;
};

}  // namespace Sinian

#endif
