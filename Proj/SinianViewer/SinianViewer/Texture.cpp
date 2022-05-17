#include "Texture.h"

#include <glad/glad.h>

using namespace std;

namespace Sinian {

Texture::Texture(std::shared_ptr<Image> image, Wrapping wrapS, Wrapping wrapT,
                 TextureFilter magFilter, TextureFilter minFilter)
    : type("Texture"),
      version(0),
      needsUpdate(false),
      image(image),
      generateMipmaps(true),
      wrapS(wrapS),
      wrapT(wrapT),
      magFilter(magFilter),
      minFilter(minFilter) {
  GetInternalFormat();
  glGenTextures(1, &texture);
}

Texture::~Texture() { glDeleteTextures(1, &texture); }

std::shared_ptr<Texture> Texture::ReadFile2Texture(
    const std::string& filePath) {
  shared_ptr<Image> image = Image::ReadFile2Image(filePath);

  shared_ptr<Texture> texture =
      make_shared<Texture>(image, RepeatWrapping, RepeatWrapping, LinearFilter,
                           LinearMipmapLinearFilter);
  return texture;
}

void Texture::GetInternalFormat() {
  internalFormat = image->Format();
  // if (glFormat == = _gl.RED) {
  //  if (glType == = _gl.FLOAT) internalFormat = _gl.R32F;
  //  if (glType == = _gl.HALF_FLOAT) internalFormat = _gl.R16F;
  //  if (glType == = _gl.UNSIGNED_BYTE) internalFormat = _gl.R8;
  //}

  // if (glFormat == = _gl.RGB) {
  //  if (glType == = _gl.FLOAT) internalFormat = _gl.RGB32F;
  //  if (glType == = _gl.HALF_FLOAT) internalFormat = _gl.RGB16F;
  //  if (glType == = _gl.UNSIGNED_BYTE) internalFormat = _gl.RGB8;
  //}

  // if (glFormat == = _gl.RGBA) {
  //  if (glType == = _gl.FLOAT) internalFormat = _gl.RGBA32F;
  //  if (glType == = _gl.HALF_FLOAT) internalFormat = _gl.RGBA16F;
  //  if (glType == = _gl.UNSIGNED_BYTE) internalFormat = _gl.RGBA8;
  //}
}

void Texture::NeedsUpdate(bool value) {
  if (value) {
    version++;
  }
}

}  // namespace Sinian