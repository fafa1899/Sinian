#include "ShaderLib.h"
#include "ShaderChunk.h"
#include "UniformsLib.h"

#include <algorithm>
#include <iterator>

using namespace std;

namespace Sinian {
ShaderLib::ShaderLib() { InitShaders(); }

ShaderLib::~ShaderLib() {}

ShaderLib &ShaderLib::GetInstance() {
  static ShaderLib instance;
  return instance;
}

void ShaderLib::InitShaders() {
  shaders.emplace("basic", InitBasic());
  shaders.emplace("lambert", InitLambert());
}

std::shared_ptr<ShaderObject> ShaderLib::InitBasic() {
  shared_ptr<ShaderObject> shaderObject = make_shared<ShaderObject>();

  shaderObject->name = "MeshBasicMaterial";
  shaderObject->uniforms = UniformsLib::GetInstance().Common();
  shaderObject->vertexShader = ShaderChunk::meshBasicVert;
  shaderObject->fragmentShader = ShaderChunk::meshBasicFrag;

  return shaderObject;
}

std::shared_ptr<ShaderObject> ShaderLib::InitLambert() {
  shared_ptr<ShaderObject> shaderObject = make_shared<ShaderObject>();

  shaderObject->name = "MeshLambertMaterial";

  auto &uniforms = shaderObject->uniforms;
  const auto &common = UniformsLib::GetInstance().Common();
  const auto &lights = UniformsLib::GetInstance().Lights();

  std::copy(common.begin(), common.end(),
            std::inserter(uniforms, uniforms.end()));
  std::copy(lights.begin(), lights.end(),
            std::inserter(uniforms, uniforms.end()));
  
  shaderObject->vertexShader = ShaderChunk::meshLambertVert;
  shaderObject->fragmentShader = ShaderChunk::meshLambertFrag;

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