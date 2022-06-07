#ifndef PROGRAMS_H
#define PROGRAMS_H

#include <map>
#include <memory>

namespace Sinian {

class Program;
class Material;
struct ShaderObject;
struct ProgramParameters;
struct LightState;

class Programs {
 public:
  Programs();

  std::shared_ptr<ProgramParameters> GetParameters(
      std::shared_ptr<Material> material, const LightState& lightState);

  std::string GetProgramCacheKey(std::shared_ptr<ProgramParameters> parameters);

  std::shared_ptr<Program> AcquireProgram(
      std::shared_ptr<ProgramParameters> parameters,
      const std::string& cacheKey);

  void ReleaseProgram(std::shared_ptr<Program> program);

 private:
  std::shared_ptr<ShaderObject> GetShaderObject(
      std::shared_ptr<Material> material, const std::string& shaderID);

  static std::map<std::string, std::string> shaderIDs;

  std::map<std::string, std::shared_ptr<Program>> programs;
};
}  // namespace Sinian

#endif
