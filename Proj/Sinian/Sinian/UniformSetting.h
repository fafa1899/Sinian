#ifndef UNIFORMSETTING_H
#define UNIFORMSETTING_H

#include <any>

namespace Sinian {

// Uniform settings required by the shader, in each frame, the material update
// will be saved in time.
// 着色器需要的Uniform设置，在每一帧中，材质的更新都会及时保存住。
struct UniformSetting {
  std::any value;
  bool needsUpdate = true;

  UniformSetting(const std::any& value, const bool& needsUpdate)
      : value(value), needsUpdate(needsUpdate) {}
  UniformSetting(const std::any& value) : UniformSetting(value, true){};
  UniformSetting() : UniformSetting(0, true) {};
};

}  // namespace Sinian

#endif