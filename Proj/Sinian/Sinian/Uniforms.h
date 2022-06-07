#ifndef SINIAN_UNIFORMS_H
#define SINIAN_UNIFORMS_H

#include <any>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Sinian {

class Uniform;
class Textures;

struct UniformSetting;

class Uniforms {
 public:
  Uniforms(unsigned int program);

  const std::vector<std::shared_ptr<Uniform>>& Seq() const { return seq; }
  const std::map<std::string, std::shared_ptr<Uniform>>& Map() const {
    return map;
  }

  static void SeqWithValue(
      const std::vector<std::shared_ptr<Uniform>>& seq,
      const std::map<std::string, UniformSetting>& values,
      std::vector<std::shared_ptr<Uniform>>& outUniformsList);

  static void Upload(const std::vector<std::shared_ptr<Uniform>>& seq,
                     const std::map<std::string, UniformSetting>& values,
                     std::shared_ptr<Textures> textures = nullptr);

  void SetValue(std::string name, std::any value,
                std::shared_ptr<Textures> textures = nullptr);

 private:
  void ParseUniform(const std::string& uniformName,
                                        unsigned int type, int addr);

  void AddUniform(std::shared_ptr<Uniform> uniformObject);

  std::vector<std::shared_ptr<Uniform>> seq;
  std::map<std::string, std::shared_ptr<Uniform>> map;
};
}  // namespace Sinian

#endif
