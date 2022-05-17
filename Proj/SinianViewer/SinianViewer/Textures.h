#ifndef SINIAN_TEXTURES_H
#define SINIAN_TEXTURES_H

#include <map>
#include <memory>

namespace Sinian {

class Properties;
class Texture;
class State;
class Image;

struct TexturePropertie;

class Textures {
 public:
  Textures(std::shared_ptr<Properties> properties,
           std::shared_ptr<State> state);

  void ResetTextureUnits();

  int AllocateTextureUnit();

  void SetTexture2D(std::shared_ptr<Texture> texture, int slot);

  void UploadTexture(std::shared_ptr<TexturePropertie> texturePropertie,
                     std::shared_ptr<Texture> texture, int slot);

 private:
  void GenerateMipmap(unsigned int target,
                      std::shared_ptr<TexturePropertie> texturePropertie,
                      int width, int height);

  bool TextureNeedsGenerateMipmaps(std::shared_ptr<Texture> texture,
                                   bool supportsMips);

  void SetTextureParameters(unsigned int textureType,
                            std::shared_ptr<Texture> texture,
                            bool supportsMips);

  // Fallback filters for non-power-of-2 textures
  unsigned int FilterFallback(unsigned int f);

  bool IsPowerOfTwo(std::shared_ptr<Image> image);

  static std::map<unsigned int, unsigned int> wrappingToGL;
  static std::map<unsigned int, unsigned int> filterToGL;

  std::shared_ptr<Properties> properties;
  std::shared_ptr<State> state;

  int textureUnits;
  int maxTextures;
};

}  // namespace Sinian

#endif