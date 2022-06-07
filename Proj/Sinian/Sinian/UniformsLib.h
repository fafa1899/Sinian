#ifndef UNIFORMSLIB_H
#define UNIFORMSLIB_H

#include "UniformSetting.h"

#include <map>
#include <string>

namespace Sinian {

// Uniform settings required by various shaders, classified according to
// reusability.
// ������ɫ����Ҫ��Uniform���ã����ݸ����Խ��з��ࡣ
class UniformsLib {
 public:
  ~UniformsLib() {}
  UniformsLib(const UniformsLib&) = delete;
  UniformsLib& operator=(const UniformsLib&) = delete;

  static UniformsLib& GetInstance();

  inline const std::map<std::string, UniformSetting>& Common() const {
    return common;
  }

  inline const std::map<std::string, UniformSetting>& Lights() const {
    return lights;
  }

 private:
  UniformsLib();

  std::map<std::string, UniformSetting> common;
  std::map<std::string, UniformSetting> lights;
};

}  // namespace Sinian

#endif
