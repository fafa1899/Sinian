#include "../ShaderChunk.h"

#include <string>

using namespace std;

namespace Sinian {
string ShaderChunk::meshBasicFrag =    
    "in vec2 TexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform vec3 diffuse;\n"
    "const float opacity = 1.0f;\n"
    "#ifdef USE_MAP\n"
    "uniform sampler2D map;\n"
    "#endif\n"
    "//uniform sampler2D mapTexture;\n"
    "void main()\n"
    "{\n"
    "  //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "  //FragColor = texture(mapTexture, TexCoord);\n"
    "  vec4 diffuseColor = vec4( diffuse, opacity );\n"
    "#ifdef USE_MAP\n"
    "  //vec4 texelColor = texture2D(map, vUv);\n"
    "  vec4 texelColor = texture2D(map, TexCoord);\n"
    "  //texelColor = mapTexelToLinear(texelColor);\n"
    "  diffuseColor *= texelColor;\n"
    "#endif\n"
    "  gl_FragColor = diffuseColor;\n"
    "}\n";
}