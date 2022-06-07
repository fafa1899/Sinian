#include "../ShaderChunk.h"

#include <string>

using namespace std;

namespace Sinian {

string ShaderChunk::meshLambertFrag =
    "in vec2 TexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform vec3 diffuse;\n"
    "const float opacity = 1.0f;\n"

    "in vec3 vLightFront;\n"
    "in vec3 vIndirectFront;\n"

    "#define RECIPROCAL_PI 0.31830988618\n"

    "struct ReflectedLight {\n"
    "	vec3 directDiffuse;\n"
    "	vec3 directSpecular;\n"
    "	vec3 indirectDiffuse;\n"
    "	vec3 indirectSpecular;\n"
    "};\n"

    "#ifdef USE_MAP\n"
    "uniform sampler2D map;\n"
    "#endif\n"

    "vec3 BRDF_Diffuse_Lambert(const in vec3 diffuseColor) {\n"
    "  return RECIPROCAL_PI * diffuseColor;\n"
    "}\n"

    "void main()\n"
    "{\n"

    "  //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "  //FragColor = texture(mapTexture, TexCoord);\n"

    "  vec4 diffuseColor = vec4( diffuse, opacity );\n"

    "  ReflectedLight reflectedLight = ReflectedLight(vec3(0.0), vec3(0.0), "
    "vec3(0.0), vec3(0.0));\n"

    "#ifdef USE_MAP\n"
    "  //vec4 texelColor = texture2D(map, vUv);\n"
    "  vec4 texelColor = texture2D(map, TexCoord);\n"
    "  //texelColor = mapTexelToLinear(texelColor);\n"
    "  diffuseColor *= texelColor;\n"
    "#endif\n"

    "  reflectedLight.indirectDiffuse += vIndirectFront;\n"
    "  reflectedLight.indirectDiffuse *= BRDF_Diffuse_Lambert( "
    "diffuseColor.rgb );\n"

    "  reflectedLight.directDiffuse = vLightFront;\n"
    "  reflectedLight.directDiffuse *= "
    "BRDF_Diffuse_Lambert(diffuseColor.rgb);\n"

    "  vec3 outgoingLight = reflectedLight.directDiffuse + "
    "reflectedLight.indirectDiffuse;\n"

	"  gl_FragColor = vec4(outgoingLight, diffuseColor.a);\n"

    "  //gl_FragColor = diffuseColor;\n"
    "}\n";
}