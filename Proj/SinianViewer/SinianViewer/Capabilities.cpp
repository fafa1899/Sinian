#include "Capabilities.h"

#include <glad/glad.h>

namespace Sinian {

Capabilities::Capabilities() {	  
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
}

Capabilities& Capabilities::GetInstance() {
  static Capabilities instance;
  return instance;
}

}  // namespace Sinian