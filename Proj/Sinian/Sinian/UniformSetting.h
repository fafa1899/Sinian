#ifndef UNIFORMSETTING_H
#define UNIFORMSETTING_H

#include <any>

namespace Sinian {

struct UniformSetting {
  std::any value;
  bool needsUpdate = true;

  UniformSetting(const std::any& value, const bool& needsUpdate)
      : value(value), needsUpdate(needsUpdate) {}
  UniformSetting(const std::any& value) : UniformSetting(value, true){};
};

}  // namespace Sinian

#endif