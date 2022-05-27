#include "ShaderLib.h"
#include "ShaderChunk.h"
#include "UniformsLib.h"

using namespace std;

namespace Sinian {
ShaderLib::ShaderLib() { InitShaders(); }

ShaderLib::~ShaderLib() {}

ShaderLib &ShaderLib::GetInstance() {
  static ShaderLib instance;
  return instance;
}

void ShaderLib::InitShaders() { shaders.emplace("basic", InitBasic()); }

std::shared_ptr<ShaderObject> ShaderLib::InitBasic() {
  shared_ptr<ShaderObject> shaderObject = make_shared<ShaderObject>();

  shaderObject->name = "MeshBasicMaterial";
  shaderObject->uniforms = UniformsLib::GetInstance().Common();
  shaderObject->vertexShader = ShaderChunk::meshBasicVert;
  shaderObject->fragmentShader = ShaderChunk::meshBasicFrag;

  return shaderObject;
}

std::shared_ptr<ShaderObject> ShaderLib::Get(const std::string &type) {
  const auto &iter = shaders.find(type);
  if (iter == shaders.end()) {
    return nullptr;
  }
  return iter->second;
}
}  // namespace Sinian