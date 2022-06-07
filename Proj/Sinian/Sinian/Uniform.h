#ifndef UNIFORM_H
#define UNIFORM_H

#include <any>
#include <string>

namespace Sinian {

class Textures;

class Uniform {
 public:
  Uniform(const std::string& id) : className("Uniform"), id(id) {}

  inline const std::string& Id() const { return id; }

  inline const std::string& ClassName() const { return className; }

  virtual void SetValue(const std::any& v,
                        std::shared_ptr<Textures> textures = nullptr) = 0;

 protected:
  std::string className;

 private:
  std::string id;
};

}  // namespace Sinian

#endif
