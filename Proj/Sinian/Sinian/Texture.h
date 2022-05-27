#ifndef SINAIN_TEXTURE_H
#define SINAIN_TEXTURE_H

#include "Image.h"
#include "SinianApi.h"

#include <string>
#include <vector>

namespace Sinian {

class SINIAN_API Texture {
 public:
  // Wrapping modes
  enum Wrapping {
    RepeatWrapping = 0,
    ClampToEdgeWrapping,
    MirroredRepeatWrapping
  };

  // Filters
  enum TextureFilter {
    NearestFilter = 0,
    NearestMipmapNearestFilter,
    NearestMipmapLinearFilter,
    LinearFilter,
    LinearMipmapNearestFilter,
    LinearMipmapLinearFilter,
  };

 public:
  Texture(std::shared_ptr<Image> image, Wrapping wrapS, Wrapping wrapT,
          TextureFilter magFilter, TextureFilter minFilter);
  ~Texture();

  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;
  Texture(Texture&& t) = delete;             // noexcept;
  Texture& operator=(Texture&& t) = delete;  // noexcept;

  static std::shared_ptr<Texture> ReadFile2Texture(const std::string& filePath);

  inline const std::string& Type() const { return type; }

  inline const int& Version() const { return version; }
  inline void Version(int version) { this->version = version; }

  void NeedsUpdate(bool value);

  inline const unsigned int& TextureId() const { return texture; }

  inline const int& Width() const { return image->Width(); }
  inline const int& Height() const { return image->Height(); }
  inline const int& DataFormat() const { return image->Format(); }
  inline const int& DataType() const { return image->Type(); }
  inline const int& InternalFormat() const { return internalFormat; }

  inline std::shared_ptr<Image> GetImage() const { return image; }

  inline const bool& GenerateMipmaps() const { return generateMipmaps; }
  void GenerateMipmaps(const bool& gen) { generateMipmaps = gen; }

  inline const std::vector<std::shared_ptr<Image>>& Mipmaps() const {
    return mipmaps;
  }

  inline const Wrapping& WrapS() const { return wrapS; }
  inline const Wrapping& WrapT() const { return wrapT; }
  inline const TextureFilter& MagFilter() const { return magFilter; }
  inline const TextureFilter& MinFilter() const { return minFilter; }

 private:
  void GetInternalFormat();

  std::string type;

  int version;  // This starts at 0 and counts how many times .needsUpdate is
                // set to true.

  // Specifies that the material needs to be updated, WebGL wise. Set it to true
  // if you made changes that need to be reflected in WebGL. This property is
  // automatically set to true when instancing a new material.
  bool needsUpdate;

  unsigned int texture;

  int internalFormat;
  std::shared_ptr<Image> image;

  bool generateMipmaps;
  std::vector<std::shared_ptr<Image>> mipmaps;

  Wrapping wrapS;
  Wrapping wrapT;
  TextureFilter magFilter;
  TextureFilter minFilter;
};

}  // namespace Sinian
#endif