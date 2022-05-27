#ifndef SHADERLIB_H
#define SHADERLIB_H

#include "ShaderObject.h"

#include <memory>

namespace Sinian {
class ShaderLib {
 public:
  ~ShaderLib();
  ShaderLib(const ShaderLib&) = delete;
  ShaderLib& operator=(const ShaderLib&) = delete;

  static ShaderLib& GetInstance();

  std::shared_ptr<ShaderObject> Get(const std::string& type);

 private:
  ShaderLib();

  void InitShaders();
  std::shared_ptr<ShaderObject> InitBasic();

  std::map<std::string, std::shared_ptr<ShaderObject>> shaders;
};
}  // namespace Sinian

#endif
