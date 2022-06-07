#ifndef STRUCTUREDUNIFORM_H
#define STRUCTUREDUNIFORM_H

#include "Uniform.h"

#include <map>
#include <memory>
#include <vector>

namespace Sinian {

class StructuredUniform
    : public Uniform,
      public std::enable_shared_from_this<StructuredUniform> {
 public:
  StructuredUniform(const std::string& id) : Uniform(id) {
    className = "StructuredUniform";
  }

  void SetValue(const std::any& v,
                std::shared_ptr<Textures> textures = nullptr);

  void SetUniform(const std::string& fullName, unsigned int type, int addr);

  void AddUniform(std::shared_ptr<Uniform> uniformObject);

  void ShowUnifom();

 private:
  std::vector<std::shared_ptr<Uniform>> seq;
  std::map<std::string, std::shared_ptr<Uniform>> map;
};

}  // namespace Sinian

#endif
