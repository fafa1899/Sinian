#ifndef PROGRAMPARAMETERS_H
#define PROGRAMPARAMETERS_H

#include <string>

namespace Sinian {
struct ShaderObject;

struct ProgramParameters {
  std::string shaderID;

  std::shared_ptr<ShaderObject> shaderObject = nullptr;

  bool map = false;
  bool specularMap = false;

  int numPointLights = 0;

  std::string Convert2KeyString();
};

}  // namespace Sinian

#endif
