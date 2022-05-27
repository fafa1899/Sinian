#ifndef SINIAN_RENDERER_H
#define SINIAN_RENDERER_H

#include "Camera.h"
#include "Object3D.h"
#include "SinianApi.h"

#include <memory>

namespace Sinian {

class Programs;
class Material;
class State;
class Textures;
class Properties;

struct MaterialPropertie;

class SINIAN_API Renderer {
 public:
  Renderer();

  void SetClearColor(const glm::vec4& color);

  void Clear(bool color = true, bool depth = true, bool stencil = true);
  void ClearColor() { Clear(true, false, false); }
  void ClearDepth() { Clear(false, true, false); }
  void ClearStencil() { Clear(false, false, true); }
   
  void SetSize(int width, int height);

  void Render(std::shared_ptr<Object3D> object, std::shared_ptr<Camera> camera);

 private:
  void SetProgram(std::shared_ptr<Material> material,
                  std::shared_ptr<Camera> camera,
                  std::shared_ptr<Object3D> object);
  void InitMaterial(std::shared_ptr<MaterialPropertie> materialPropertie,
                    std::shared_ptr<Material> material);

  // Todo:Program And Material Need Be Release
  std::shared_ptr<Programs> programCache;
  std::shared_ptr<Properties> properties;

  std::shared_ptr<State> state;
  std::shared_ptr<Textures> textures;

  int currentMaterialId;
  std::shared_ptr<Camera> currentCamera;
};
}  // namespace Sinian

#endif