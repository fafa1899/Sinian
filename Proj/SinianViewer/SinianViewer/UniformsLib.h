#ifndef UNIFORMSLIB_H
#define UNIFORMSLIB_H

#include "UniformSetting.h"

#include <map>
#include <string>

namespace Sinian {

class UniformsLib {
 public:
  ~UniformsLib() {}
  UniformsLib(const UniformsLib&) = delete;
  UniformsLib& operator=(const UniformsLib&) = delete;

  static UniformsLib& GetInstance();

  inline const std::map<std::string, UniformSetting>& Common() const {
    return common;
  }

 private:
  UniformsLib();

  std::map<std::string, UniformSetting> common;
};

}  // namespace Sinian

#endif
