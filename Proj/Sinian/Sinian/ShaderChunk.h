#ifndef SHADERCHUNK_H
#define SHADERCHUNK_H

#include <string>

namespace Sinian {

class ShaderChunk {
 public:
  static std::string meshBasicVert;
  static std::string meshBasicFrag;

  static std::string meshLambertVert;
  static std::string meshLambertFrag;

  static std::string meshPhongVert;
  static std::string meshPhongFrag;
};

}  // namespace Sinian

#endif