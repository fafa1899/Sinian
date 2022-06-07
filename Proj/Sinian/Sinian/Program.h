#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>

namespace Sinian {

struct ProgramParameters;

class Uniforms;

class Program {
 public:
  Program(const std::string& cacheKey,
          std::shared_ptr<ProgramParameters> parameters);

  ~Program();

  Program(const Program&) = delete;
  Program& operator=(const Program&) = delete;
  Program(Program&& t) = delete;             // noexcept;
  Program& operator=(Program&& t) = delete;  // noexcept;

  inline const std::string& CacheKey() const { return cacheKey; }

  inline const int& UsedTimes() const { return usedTimes; }
  void UsedTimes(const int& usedTimes) { this->usedTimes = usedTimes; }

  inline const unsigned int& ProgramId() const { return program; }

  std::shared_ptr<Uniforms> GetUniforms();

 private:
  std::string cacheKey;  // unique identifier for this program, used
                         // for looking up compiled programs from cache.
  std::string name;

  int usedTimes;

  unsigned int program;

  std::shared_ptr<Uniforms> cachedUniforms;

  std::string& ReplaceLightNums(std::string& shaderString,
                           std::shared_ptr<ProgramParameters> parameters);

  unsigned int CompileShader(std::string vertexCode, unsigned int shaderType);

  void CheckShaderErrors(unsigned int shader);

  void CleanShader(unsigned int shaderId);

  void CheckProgramErrors(unsigned int program);
};
}  // namespace Sinian

#endif
