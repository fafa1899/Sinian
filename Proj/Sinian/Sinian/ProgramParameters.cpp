#include "ProgramParameters.h"

#include <string>

using namespace std;

namespace Sinian {

std::string ProgramParameters::Convert2KeyString() {
  return to_string(map) + "," + to_string(numPointLights);
}

}  // namespace Sinian
