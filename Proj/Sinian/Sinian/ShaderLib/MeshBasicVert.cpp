#include "../ShaderChunk.h"

#include <string>

using namespace std;

namespace Sinian {
string ShaderChunk::meshBasicVert =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 modelMatrix;\n"
    "uniform mat4 viewMatrix;\n"
    "uniform mat4 projectionMatrix;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0f);\n"
    "   TexCoord = aTexCoord;\n"
    "}\n";
}  // namespace Sinian
