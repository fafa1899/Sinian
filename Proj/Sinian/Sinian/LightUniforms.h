#ifndef LIGHTUNIFORMS_H
#define LIGHTUNIFORMS_H

#include "UniformSetting.h"

#include <map>
#include <memory>

namespace Sinian {

class Light;

class LightUniforms {
 public:
  std::map<std::string, UniformSetting>& Get(std::shared_ptr<Light> light);

 private:
  std::map<int, std::map<std::string, UniformSetting>> lights;
};

}  // namespace Sinian

#endif
