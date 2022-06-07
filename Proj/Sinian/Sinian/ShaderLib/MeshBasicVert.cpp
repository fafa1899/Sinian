#include "../ShaderChunk.h"

#include <string>

using namespace std;

namespace Sinian {
string ShaderChunk::meshBasicVert = 
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0f);\n"
    "   TexCoord = aTexCoord;\n"
    "}\n";
}  // namespace Sinian
