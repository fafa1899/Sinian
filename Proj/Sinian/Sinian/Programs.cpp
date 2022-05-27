#include "Programs.h"
#include "Material.h"
#include "MeshBasicMaterial.h"
#include "Program.h"
#include "ProgramParameters.h"
#include "ShaderLib.h"
#include "ShaderObject.h"

using namespace std;

namespace Sinian {
Programs::Programs() {}

std::map<std::string, std::string> Programs::shaderIDs = {
    {"MeshBasicMaterial", "basic"}};

std::shared_ptr<ProgramParameters> Programs::GetParameters(
    std::shared_ptr<Material> material) {
  shared_ptr<ProgramParameters> parameters = make_shared<ProgramParameters>();

  string shaderID;
  const auto& sIter = shaderIDs.find(material->Type());
  if (sIter != shaderIDs.end()) {
    shaderID = sIter->second;
  }

  std::shared_ptr<ShaderObject> shaderobject =
      GetShaderObject(material, shaderID);
  parameters->shaderID = shaderID;
  parameters->shaderObject = shaderobject;

  if (material->Type() == "MeshBasicMaterial") {
    std::shared_ptr<MeshBasicMaterial> meshBasicMaterial =
        static_pointer_cast<MeshBasicMaterial>(material);
    parameters->map = meshBasicMaterial->Map() ? true : false;
  }

  return parameters;
}

std::string Programs::GetProgramCacheKey(
    std::shared_ptr<ProgramParameters> parameters) {
  string cacheKey;

  if (parameters->shaderID.empty()) {
    cacheKey += parameters->shaderObject->vertexShader;
    cacheKey += ";";
    cacheKey += parameters->shaderObject->fragmentShader;
    cacheKey += ";";
  } else {
    cacheKey += parameters->shaderID;
    cacheKey += ";";
  }

  cacheKey = cacheKey + parameters->Convert2KeyString();

  return cacheKey;
}

std::shared_ptr<Program> Programs::AcquireProgram(
    std::shared_ptr<ProgramParameters> parameters,
    const std::string& cacheKey) {
  const auto& iter = programs.find(cacheKey);
  if (iter != programs.end()) {
    return iter->second;
  }

  shared_ptr<Program> program = make_shared<Program>(cacheKey, parameters);
  programs.emplace(cacheKey, program);

  return program;
}

std::shared_ptr<ShaderObject> Programs::GetShaderObject(
    std::shared_ptr<Material> material, const std::string& shaderID) {
  std::shared_ptr<ShaderObject> shaderobject =
      ShaderLib::GetInstance().Get(shaderID);
  if (!shaderobject) {
    printf("Need implement£¡");
  }

  return shaderobject;
}

}  // namespace Sinian