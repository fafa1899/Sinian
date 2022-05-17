#ifndef SINIAN_STATE_H
#define SINIAN_STATE_H

#include <glad/glad.h>

#include <map>
#include <memory>

namespace Sinian {

struct MiniTexture {
  unsigned int type = GL_TEXTURE_2D;
  unsigned int id = 0;
};

class Image;

class State {
 public:
  State();

  bool UseProgram(GLuint program);

  // texture
  void ActiveTexture(int slot);
  void BindTexture(unsigned int type, unsigned int textureID);
  void UnbindTexture();
  //void TexImage2D(unsigned int target, int level, int internalformat, int width,
  //                int height, int border, unsigned int format,
  //                unsigned int type, const void *data);
  void TexImage2D(unsigned int target, int level, int internalformat, std::shared_ptr<Image> image);

 private:
  GLuint currentProgram;
  int currentTextureSlot;

  std::map<int, MiniTexture> currentBoundTextures;
};
}  // namespace Sinian

#endif
