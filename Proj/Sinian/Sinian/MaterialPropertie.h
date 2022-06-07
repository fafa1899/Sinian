#ifndef MATERIALPROPERTIE_H
#define MATERIALPROPERTIE_H

#include <memory>
#include <vector>

namespace Sinian {
struct ShaderObject;

class Program;
class Uniform;

struct MaterialPropertie {
  int version = -1;

  bool needsLights = false;
  int lightsStateVersion = -1;
  
  std::shared_ptr<Program> program = nullptr;
  std::shared_ptr<ShaderObject> shaderObject = nullptr;
  std::vector<std::shared_ptr<Uniform>> uniformsList;  
};
}  // namespace Sinian

#endif
