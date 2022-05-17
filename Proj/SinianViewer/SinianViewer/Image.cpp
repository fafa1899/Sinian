#include "Image.h"
#include <glad/glad.h>

#include <stb_image.h>

#include <iostream>

using namespace std;

namespace Sinian {

Image::Image(int width, int height, int format, int type)
    : width(width), height(height), format(format), type(type) {

  switch (format) {
    case GL_RED:
    default:
      channels = 1;
      break;
    case GL_RG:
      channels = 2;
      break;
    case GL_RGB:
    case GL_BGR:
      channels = 3;
      break;
    case GL_RGBA:
    case GL_BGRA:
      channels = 4;
      break;
  }

  switch (type) {
    case GL_UNSIGNED_BYTE:
    case GL_BYTE:
    default:
      bytes = 1;
      break;
    case GL_UNSIGNED_SHORT:
    case GL_SHORT:
      bytes = 2;
      break;
    case GL_UNSIGNED_INT:
    case GL_INT:
      bytes = 4;
      break;
    case GL_FLOAT:
      bytes = 4;
      break;
  }
   
  size_t dataSize = size_t(width) * height * channels * bytes;
  data = make_unique<char[]>(dataSize); 
}

std::shared_ptr<Image> Image::ReadFile2Image(const std::string& filePath) {
  // tell stb_image.h to flip loaded texture's on the y-axis.
  stbi_set_flip_vertically_on_load(true);

 
  int width, height, nrComponents;
  unsigned char* data =
      stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
  
  std::shared_ptr<Image> image =
      make_shared<Image>(width, height, GL_RGB, GL_UNSIGNED_BYTE);

  unsigned char* imageData = image->GetData();
  size_t dataSize = (size_t)width * height * nrComponents;
   
  memcpy(imageData, data, dataSize);

  stbi_image_free(data);

  return image; 
}

unsigned char* Image::GetData() { return (unsigned char*)(data.get()); }

}  // namespace Sinian