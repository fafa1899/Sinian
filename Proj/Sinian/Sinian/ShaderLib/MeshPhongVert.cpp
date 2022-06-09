#include "../ShaderChunk.h"

#include <string>

using namespace std;

namespace Sinian {

string ShaderChunk::meshPhongVert =
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
  
	"out vec3 vViewPosition;\n"
	"#ifndef FLAT_SHADED\n"
    "	out vec3 vNormal;\n"
	"#endif\n"
	 
    "void main()\n"
    "{\n"

    "  vec3 objectNormal = vec3(normal);"

    "  vec3 transformedNormal = objectNormal;\n"
    "  transformedNormal = normalMatrix * transformedNormal;"

    "  vec3 transformed = vec3(position);\n"
    "  vec4 worldPosition = vec4(transformed, 1.0);\n"
    "  worldPosition = modelMatrix * worldPosition;\n"

	"#ifndef FLAT_SHADED // Normal computed with derivatives when FLAT_SHADED\n"
	"  vNormal = normalize(transformedNormal);\n"
	"#endif\n"

    "  vec4 mvPosition = vec4(transformed, 1.0);\n"
    "  mvPosition = modelViewMatrix * mvPosition;"
    "  gl_Position = projectionMatrix * mvPosition;\n"

	"  vViewPosition = - mvPosition.xyz;"

    "  TexCoord = aTexCoord;\n"

    "}\n";

}  // namespace Sinian
