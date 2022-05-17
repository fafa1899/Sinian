#ifndef TEXTUREPROPERTIE_H
#define TEXTUREPROPERTIE_H

#include <memory>
#include <vector>

namespace Sinian {

struct TexturePropertie {
  int version = -1;
  unsigned int texture = 0;
  int maxMipLevel = 0;
};

}  // namespace Sinian

#endif
