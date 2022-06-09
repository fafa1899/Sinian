#include "Programs.h"
#include "LightState.h"
#include "Materials/Material.h"
#include "Materials/MeshBasicMaterial.h"
#include "Materials/MeshLambertMaterial.h"
#include "Materials/MeshPhongMaterial.h"
#include "Program.h"
#include "ProgramParameters.h"
#include "ShaderLib.h"
#include "ShaderObject.h"

using namespace std;

namespace Sinian {
Programs::Programs() {}

std::map<std::string, std::string> Programs::shaderIDs = {
    {"MeshBasicMaterial", "basic"},
    {"MeshLambertMaterial", "lambert"},
    {"MeshPhongMaterial", "phong"}};

std::shared_ptr<ProgramParameters> Programs::GetParameters(
    std::shared_ptr<Material> material, const LightState& lightState) {
  //
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
    //
    std::shared_ptr<MeshBasicMaterial> meshBasicMaterial =
        static_pointer_cast<MeshBasicMaterial>(material);
    parameters->map = meshBasicMaterial->Map() ? true : false;
  } else if (material->Type() == "MeshLambertMaterial") {
    //
    std::shared_ptr<MeshLambertMaterial> meshLambertMaterial =
        static_pointer_cast<MeshLambertMaterial>(material);
    parameters->map = meshLambertMaterial->Map() ? true : false;
  } else if (material->Type() == "MeshPhongMaterial") {
    //
    std::shared_ptr<MeshPhongMaterial> meshPhongMaterial =
        static_pointer_cast<MeshPhongMaterial>(material);
    parameters->map = meshPhongMaterial->Map() ? true : false;
    parameters->specularMap = meshPhongMaterial->SpecularMap() ? true : false;
  }

  parameters->numPointLights = int(lightState.point.size());

  return parameters;
}

std::string Programs::GetProgramCacheKey(
    std::shared_ptr<ProgramParameters> parameters) {
  //
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
    auto program = iter->second;
    program->UsedTimes(program->UsedTimes() + 1);
    return program;
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

void Programs::ReleaseProgram(std::shared_ptr<Program> program) {
  program->UsedTimes(program->UsedTimes() - 1);
  if (program->UsedTimes() == 0) {
    const auto& iter = programs.find(program->CacheKey());
    if (iter != programs.end()) {
      programs.erase(iter);
    }

    // Free WebGL resources
    // program.destroy();
  }
}

}  // namespace Sinian