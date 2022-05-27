#pragma once

#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include "UniformSetting.h"

#include <map>
#include <string>

namespace Sinian {
struct ShaderObject {
  std::string name;

  std::map<std::string, UniformSetting> uniforms;

  std::string vertexShader;
  std::string fragmentShader;
};
}  // namespace Sinian

#endif