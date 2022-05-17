#include "State.h"
#include "Capabilities.h"
#include "Image.h"

#include <limits.h>
#include <iostream>

using namespace std;

namespace Sinian {

State::State() : currentProgram(UINT32_MAX) {
  // Texture unit 0 is activated by default
  currentTextureSlot = 0; /*Capabilities::GetInstance().MaxTextures()*/
}

bool State::UseProgram(GLuint program) {
  if (currentProgram != program) {
    glUseProgram(program);
    currentProgram = program;

    return true;
  }

  return false;
}

void State::ActiveTexture(int slot) {
  if (currentTextureSlot != slot) {
    glActiveTexture(slot);
    currentTextureSlot = slot;
  }
}

void State::BindTexture(unsigned int type, unsigned int textureID) {
  MiniTexture &boundTexture = currentBoundTextures[currentTextureSlot];

  if (boundTexture.type != type || boundTexture.id != textureID) {
    glBindTexture(type, textureID);
    boundTexture.type = type;
    boundTexture.id = textureID;
  }
}

void State::UnbindTexture() {
  const auto &iter = currentBoundTextures.find(currentTextureSlot);
  if (iter != currentBoundTextures.end()) {
    glBindTexture(iter->second.type, NULL);
    iter->second.type = GL_TEXTURE_2D;
    iter->second.id = 0;
  }
}

//void State::TexImage2D(unsigned int target, int level, int internalformat,
//                       int width, int height, int border, unsigned int format,
//                       unsigned int type, const void *data) {
//  glTexImage2D(target, level, internalformat, width, height, border, format,
//               type, data);
//  // glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
//  // GL_UNSIGNED_BYTE, data);
//}

void State::TexImage2D(unsigned int target, int level, int internalformat,
	std::shared_ptr<Image> image) {
  glTexImage2D(target, level, internalformat, image->Width(), image->Height(),
               0, image->Format(), image->Type(), image->GetData());
}

}  // namespace Sinian