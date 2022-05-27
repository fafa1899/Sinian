#ifndef SINAIN_IMAGE_H
#define SINAIN_IMAGE_H

#include <memory>
#include <string>

namespace Sinian {

// Image classes expressed in memory can usually be processed by the CPU;
// uploaded to video memory, they become texture classes.
class Image {
 public:
  Image(int width, int height, int format, int type);

  static std::shared_ptr<Image> ReadFile2Image(const std::string& filePath);

  inline const int& Width() const { return width; }
  inline const int& Height() const { return height; }
  inline const int& Format() const { return format; }
  inline const int& Type() const { return type; }

  unsigned char* GetData(); 
  
 private:
  int width;
  int height;
  int format;
  int type;

  int channels;
  int bytes;
  std::unique_ptr<char[]> data; 
};

}  // namespace Sinian

#endif
