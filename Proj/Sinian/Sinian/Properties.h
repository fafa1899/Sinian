#ifndef SINIAN_PROPERTIES_H
#define SINIAN_PROPERTIES_H

#include <map>
#include <memory>

namespace Sinian {

class Material;
class Texture;

struct MaterialPropertie;
struct TexturePropertie;

// Used to store various attributes required for graphics rendering, including
// materials, textures, etc.
class Properties {
 public:

 public:
  Properties() {}

  std::shared_ptr<MaterialPropertie> Get(std::shared_ptr<Material> material);

  std::shared_ptr<TexturePropertie> Get(std::shared_ptr<Texture> texture);

  // remove(object : any) : void;
  // update(object : any, key : any, value : any) : any;
  // void dispose(){};

 private:
  std::map<std::shared_ptr<Material>, std::shared_ptr<MaterialPropertie>>
      materialProperties;

  std::map<std::shared_ptr<Texture>, std::shared_ptr<TexturePropertie>>
      textureProperties;
};

}  // namespace Sinian

#endif
