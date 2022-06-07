#include "../ShaderChunk.h"

#include <string>

using namespace std;

namespace Sinian {

string ShaderChunk::meshLambertVert =
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "out vec3 vLightFront;\n"
    "out vec3 vIndirectFront;\n"

	"#define PI 3.14159265359\n"

	"#define saturate(a) clamp(a, 0.0, 1.0)\n"

    "struct IncidentLight {\n"
    "  vec3 color;\n "
    "  vec3 direction;\n "
    "  bool visible;\n"
    "};\n"

    "struct GeometricContext {\n"
    "  vec3 position;\n"
    "  vec3 normal;\n"
    "  vec3 viewDir;\n"
    "};\n"

    "float punctualLightIntensityToIrradianceFactor( const in float "
    "  lightDistance, const in float cutoffDistance, const in float "
    "  decayExponent ) {\n"
    "  if(cutoffDistance > 0.0 && decayExponent > 0.0) {\n"
	"    return pow(saturate(-lightDistance / cutoffDistance + 1.0), decayExponent);\n"
	"  }\n"
	"  return 1.0;\n"
    "}\n"

    "uniform vec3 ambientLightColor;\n"

    "vec3 getAmbientLightIrradiance(const in vec3 ambientLightColor) { \n"
    "  vec3 irradiance = ambientLightColor;\n"
    "  #ifndef PHYSICALLY_CORRECT_LIGHTS\n"
    "    irradiance *= PI;\n"
    "  #endif\n"
    "  return irradiance;\n"
    "}\n"

    "#if NUM_POINT_LIGHTS > 0\n"
    "struct PointLight {\n"
    "  vec3 position;\n"
    "  vec3 color;\n"
    "  float distance;\n"
    "  float decay;\n"
    "};\n"
    "uniform PointLight pointLights[NUM_POINT_LIGHTS];\n"

    "// directLight is an out parameter as having it as a return value caused"
    " compiler errors on some devices\n"
    "void getPointDirectLightIrradiance(const in PointLight pointLight,"
    "  const in GeometricContext geometry, out IncidentLight directLight){\n"
    "  //vec3 lVector = vec3(1.2f,1.0f,-3.0) - geometry.position;\n"
    "  vec3 lVector = pointLight.position - geometry.position;\n"
    "  directLight.direction = normalize(lVector);\n"
    "  float lightDistance = length(lVector);\n"
    "  directLight.color = pointLight.color;\n"
    "  directLight.color *= punctualLightIntensityToIrradianceFactor(\n"
    "    lightDistance, pointLight.distance, pointLight.decay);\n"
    "  directLight.visible = (directLight.color != vec3(0.0));\n"
    "}\n"

    "#endif\n"

    "void main()\n"
    "{\n"

    "  vec3 objectNormal = vec3(normal);"

    "  vec3 transformedNormal = objectNormal;\n"
    "  transformedNormal = normalMatrix * transformedNormal;"

    "  vec3 transformed = vec3(position);\n"
    "  vec4 worldPosition = vec4(transformed, 1.0);\n"
    "  worldPosition = modelMatrix * worldPosition;\n"

    "  vec4 mvPosition = vec4(transformed, 1.0);\n"
    "  mvPosition = modelViewMatrix * mvPosition;"
    "  gl_Position = projectionMatrix * mvPosition;\n"

    "  TexCoord = aTexCoord;\n"

    "  GeometricContext geometry;\n"
    "  geometry.position = mvPosition.xyz;\n"
    "  geometry.normal = normalize(transformedNormal);\n"
    "  geometry.viewDir = normalize(-mvPosition.xyz);\n"

    "  vLightFront = vec3(0.0);\n"
    "  vIndirectFront = vec3(0.0);\n"

    "  IncidentLight directLight;\n" 
	"  float dotNL;\n"
	"  vec3 directLightColor_Diffuse;\n"

    "  vIndirectFront += getAmbientLightIrradiance(ambientLightColor);\n"

    "  #if NUM_POINT_LIGHTS > 0\n"
    "  for ( int i = 0; i < NUM_POINT_LIGHTS; i ++ ) {\n"
    "    getPointDirectLightIrradiance(pointLights[i],geometry,directLight);\n"
	"    dotNL = dot(geometry.normal, directLight.direction);\n" 
	"    directLightColor_Diffuse = PI * directLight.color;\n"
    "    vLightFront += saturate( dotNL ) * directLightColor_Diffuse;\n"
    "  }\n"
    "  #endif\n"

    "}\n";

}  // namespace Sinian
