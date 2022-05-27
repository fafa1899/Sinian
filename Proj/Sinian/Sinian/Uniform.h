#ifndef UNIFORM_H
#define UNIFORM_H

#include <any>
#include <string>

namespace Sinian {

class Textures;

class Uniform {
 public:
  Uniform(const char* id) : id(id) {}

  inline const std::string& Id() const { return id; }

  virtual void SetValue(const std::any& v,
                        std::shared_ptr<Textures> textures = nullptr) = 0;

 private:
  std::string id;
};

}  // namespace Sinian

#endif
