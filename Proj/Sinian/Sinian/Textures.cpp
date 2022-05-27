#include "Textures.h"
#include "Capabilities.h"
#include "MathUtils.h"
#include "Properties.h"
#include "State.h"
#include "Texture.h"
#include "TexturePropertie.h"

#include <glad/glad.h>

#include <algorithm>
#include <iostream>

using namespace std;

namespace Sinian {

std::map<unsigned int, unsigned int> Textures::wrappingToGL = {
    {Texture::RepeatWrapping, GL_REPEAT},
    {Texture::ClampToEdgeWrapping, GL_CLAMP_TO_EDGE},
    {Texture::MirroredRepeatWrapping, GL_MIRRORED_REPEAT}};

std::map<unsigned int, unsigned int> Textures::filterToGL = {
    {Texture::NearestFilter, GL_NEAREST},
    {Texture::NearestMipmapNearestFilter, GL_NEAREST_MIPMAP_NEAREST},
    {Texture::NearestMipmapLinearFilter, GL_NEAREST_MIPMAP_LINEAR},
    {Texture::LinearFilter, GL_LINEAR},
    {Texture::LinearMipmapNearestFilter, GL_LINEAR_MIPMAP_NEAREST},
    {Texture::LinearMipmapLinearFilter, GL_LINEAR_MIPMAP_LINEAR}};

Textures::Textures(std::shared_ptr<Properties> properties,
                   std::shared_ptr<State> state)
    : properties(properties), state(state), textureUnits(0) {
  const auto& capabilities = Capabilities::GetInstance();
  maxTextures = capabilities.MaxTextures();
}

void Textures::ResetTextureUnits() { textureUnits = 0; }

int Textures::AllocateTextureUnit() {
  int textureUnit = textureUnits;

  if (textureUnit >= maxTextures) {
    printf(
        "THREE.WebGLTextures: Trying to use %d texture units while this GPU "
        "supports only %d",
        textureUnit, maxTextures);
  }

  textureUnits += 1;
  return textureUnit;
}

void Textures::SetTexture2D(std::shared_ptr<Texture> texture, int slot) {
  shared_ptr<TexturePropertie> texturePropertie = properties->Get(texture);

  if (texturePropertie->version != texture->Version()) {
    shared_ptr<Image> image = texture->GetImage();

    bool imageComplete = false;

    if (!image) {
      printf("Renderer: Texture marked for update but image is undefined");
    } else if (imageComplete) {
      // Todo£ºHandle image loading asynchronously
      printf("Renderer: Texture marked for update but image is incomplete");
    } else {
      UploadTexture(texturePropertie, texture, slot);
    }
  }

  state->ActiveTexture(GL_TEXTURE0 + slot);
  state->BindTexture(GL_TEXTURE_2D, texturePropertie->texture);
}

void Textures::UploadTexture(std::shared_ptr<TexturePropertie> texturePropertie,
                             std::shared_ptr<Texture> texture, int slot) {
  GLenum textureType = GL_TEXTURE_2D;
  // if (texture.isDataTexture2DArray) textureType = _gl.TEXTURE_2D_ARRAY;
  // if (texture.isDataTexture3D) textureType = _gl.TEXTURE_3D;

  // initTexture(textureProperties, texture);
  texturePropertie->texture = texture->TextureId();

  state->ActiveTexture(GL_TEXTURE0 + slot);
  state->BindTexture(textureType, texturePropertie->texture);

  //_gl.pixelStorei(_gl.UNPACK_FLIP_Y_WEBGL, texture.flipY);
  //_gl.pixelStorei(_gl.UNPACK_PREMULTIPLY_ALPHA_WEBGL,
  // texture.premultiplyAlpha); _gl.pixelStorei(_gl.UNPACK_ALIGNMENT,
  // texture.unpackAlignment);

  // Todo: Processed to a power of 2
  // var needsPowerOfTwo = textureNeedsPowerOfTwo(texture) &&
  // isPowerOfTwo(texture.image) == false; var image =
  // resizeImage(texture.image, needsPowerOfTwo, false, maxTextureSize);

  bool supportsMips = IsPowerOfTwo(texture->GetImage());

  SetTextureParameters(textureType, texture, supportsMips);

  const auto& mipmaps = texture->Mipmaps();

  if (texture->Type() == "DepthTexture") {
  } else if (texture->Type() == "DataTexture") {
  } else if (texture->Type() == "CompressedTexture") {
  } else if (texture->Type() == "DataTexture2DArray") {
  } else if (texture->Type() == "DataTexture3D") {
  } else {
    // regular Texture (image, video, canvas)

    // use manually created mipmaps if available if there are no manual
    // mipmaps set 0 level mipmap and then use GL to generate other mipmap
    // levels

    if (mipmaps.size() > 0 && supportsMips) {
      int length = (int)(mipmaps.size());
      for (int i = 0; i < length; i++) {
        state->TexImage2D(GL_TEXTURE_2D, i, texture->InternalFormat(),
                          mipmaps[i]);
      }
      texture->GenerateMipmaps(false);
      texturePropertie->maxMipLevel = length - 1;
    } else {
      state->TexImage2D(GL_TEXTURE_2D, 0, texture->InternalFormat(),
                        texture->GetImage());
      texturePropertie->maxMipLevel = 0;
    }
  }

  if (TextureNeedsGenerateMipmaps(texture, supportsMips)) {
    GenerateMipmap(textureType, texturePropertie, texture->Width(),
                   texture->Height());
  }

  texturePropertie->version = texture->Version();

  // if (texture.onUpdate) texture.onUpdate(texture);
}

void Textures::GenerateMipmap(
    unsigned int target, std::shared_ptr<TexturePropertie> texturePropertie,
    int width, int height) {
  glGenerateMipmap(target);

  texturePropertie->maxMipLevel = (int)log2((std::max)(width, height));
}

bool Textures::TextureNeedsGenerateMipmaps(std::shared_ptr<Texture> texture,
                                           bool supportsMips) {
  return texture->GenerateMipmaps() && supportsMips &&
         texture->MinFilter() != Texture::NearestFilter &&
         texture->MinFilter() != Texture::LinearFilter;
}

void Textures::SetTextureParameters(unsigned int textureType,
                                    std::shared_ptr<Texture> texture,
                                    bool supportsMips) {
  //
  if (supportsMips) {
    glTexParameteri(textureType, GL_TEXTURE_WRAP_S,
                    wrappingToGL[texture->WrapS()]);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T,
                    wrappingToGL[texture->WrapT()]);

    if (textureType == GL_TEXTURE_3D || textureType == GL_TEXTURE_2D_ARRAY) {
      // glTexParameteri(textureType, GL_TEXTURE_WRAP_R,
      // wrappingToGL[texture.wrapR]);
    }

    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER,
                    filterToGL[texture->MagFilter()]);
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER,
                    filterToGL[texture->MinFilter()]);
  } else {
    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (textureType == GL_TEXTURE_3D || textureType == GL_TEXTURE_2D_ARRAY) {
      glTexParameteri(textureType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    if (texture->WrapS() != Texture::ClampToEdgeWrapping ||
        texture->WrapT() != Texture::ClampToEdgeWrapping) {
      printf(
          "THREE.WebGLRenderer: Texture is not power of two. Texture.wrapS "
          "and "
          "Texture.wrapT should be set to THREE.ClampToEdgeWrapping.");
    }

    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER,
                    FilterFallback(texture->MagFilter()));
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER,
                    FilterFallback(texture->MinFilter()));

    if (texture->MinFilter() != Texture::NearestFilter &&
        texture->MinFilter() != Texture::LinearFilter) {
      printf(
          "THREE.WebGLRenderer: Texture is not power of two. "
          "Texture.minFilter "
          "should be set to THREE.NearestFilter or THREE.LinearFilter.");
    }
  }

  // Todo£ºHandle anisotropy
}

// Fallback filters for non-power-of-2 textures
unsigned int Textures::FilterFallback(unsigned int f) {
  if (f == Texture::NearestFilter || f == Texture::NearestMipmapNearestFilter ||
      f == Texture::NearestMipmapLinearFilter) {
    return GL_NEAREST;
  }

  return GL_LINEAR;
}

bool Textures::IsPowerOfTwo(std::shared_ptr<Image> image) {
  return MathUtils::IsPowerOfTwo(image->Width()) &&
         MathUtils::IsPowerOfTwo(image->Height());
}

}  // namespace Sinian