#ifndef SINIAN_MATERIAL_H
#define SINIAN_MATERIAL_H

#include <map>
#include <vector>

#include "RenderState.h"
#include "Shader.h"
#include "SinianApi.h"

namespace Sinian {
class Texture2D;

class SINIAN_API Material {
 public:
  Material();
  virtual ~Material();

  void Update();

  inline const std::string &Type() const { return type; }

  inline const int &Id() const { return id; }

  inline const int &Version() const { return version; }
  inline void Version(int version) { this->version = version; }

  void NeedsUpdate(bool value);

  const std::vector<std::shared_ptr<Texture2D>> &Textures() const {
    return textures;
  }

  //void SetUniform(const std::string &name, std::any value);
  //void SetUniforms(const std::map<std::string, std::any> &uniforms);

  const bool &DepthTest() { return renderState.depthTest.enabled; }
  void DepthTest(const bool &enabled) {
    renderState.depthTest.enabled = enabled;
  }

  const GLenum &DepthFunc() { return renderState.depthTest.func; }
  void DepthFunc(const GLenum &func) { renderState.depthTest.func = func; }

  const bool &CullEnabled() { return renderState.cull.enabled; }
  void CullEnabled(const bool &enabled) { renderState.cull.enabled = enabled; }

 protected:
  static int materialId;

  std::string type;
  int id;

  int version;  // This starts at 0 and counts how many times .needsUpdate is
                // set to true.

  // Specifies that the material needs to be updated, WebGL wise. Set it to true
  // if you made changes that need to be reflected in WebGL. This property is
  // automatically set to true when instancing a new material.
  bool needsUpdate;

  //void SetUniformValue(const std::string &name, std::any value);

  std::map<std::string, int> textureNameAndTextureUnit;
  std::vector<std::shared_ptr<Texture2D>> textures;

  RenderState renderState;
};
}  // namespace Sinian

#endif
