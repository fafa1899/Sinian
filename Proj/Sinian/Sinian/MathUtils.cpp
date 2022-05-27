#include "MathUtils.h"

namespace Sinian {

bool MathUtils::IsPowerOfTwo(int value) {
  return (value & (value - 1)) == 0 && value != 0;
}

}  // namespace Sinian
