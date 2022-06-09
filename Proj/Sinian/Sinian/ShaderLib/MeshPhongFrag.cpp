#include "../ShaderChunk.h"

#include <string>

using namespace std;

namespace Sinian {

string ShaderChunk::meshPhongFrag =
    "in vec2 TexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform vec3 diffuse;\n"
    "uniform vec3 specular;\n"
    "uniform float shininess;\n"
    "const float opacity = 1.0f;\n"
	   
	"#define PI 3.14159265359\n"
    "#define RECIPROCAL_PI 0.31830988618\n"
	   
    "struct ReflectedLight {\n"
    "	vec3 directDiffuse;\n"
    "	vec3 directSpecular;\n"
    "	vec3 indirectDiffuse;\n"
    "	vec3 indirectSpecular;\n"
    "};\n"

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

    "#ifdef USE_MAP\n"
    "uniform sampler2D map;\n"
    "#endif\n"

    "vec3 BRDF_Diffuse_Lambert(const in vec3 diffuseColor) {\n"
    "  return RECIPROCAL_PI * diffuseColor;\n"
    "}\n"

	"vec3 F_Schlick( const in vec3 specularColor, const in float dotLH ) {\n"
	"// Original approximation by Christophe Schlick '94\n"
    "// float fresnel = pow( 1.0 - dotLH, 5.0 );\n"
    "// Optimized variant (presented by Epic at SIGGRAPH '13)\n"
    "// https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf \n"
    "  float fresnel = exp2((-5.55473 * dotLH - 6.98316) * dotLH);\n"
	"  return (1.0 - specularColor) * fresnel + specularColor;\n"
    "} // validated\n"

	"float G_BlinnPhong_Implicit(/* const in float dotNL, const in float dotNV */) {\n"
		// geometry term is (n dot l)(n dot v) / 4(n dot l)(n dot v)
	"  return 0.25;\n"
    "}\n"

    "float D_BlinnPhong(const in float shininess, const in float dotNH) {\n"
		"return RECIPROCAL_PI * (shininess * 0.5 + 1.0) * pow(dotNH, shininess);\n"
	"}\n"

	"vec3 BRDF_Specular_BlinnPhong(const in IncidentLight incidentLight," 
	  "const in GeometricContext geometry, const in vec3 specularColor," 
	  "const in float shininess) {\n"
	"  vec3 halfDir = normalize(incidentLight.direction + geometry.viewDir);\n"
    "  // float dotNL = saturate(dot(geometry.normal, incidentLight.direction));\n"
    "  // float dotNV = saturate(dot(geometry.normal, geometry.viewDir));\n"
    "  float dotNH = saturate(dot(geometry.normal, halfDir));\n"
    "  float dotLH = saturate(dot(incidentLight.direction, halfDir));\n"
	"  vec3 F = F_Schlick(specularColor, dotLH);\n"
	"  float G = G_BlinnPhong_Implicit(/* dotNL, dotNV */);\n"
	"  float D = D_BlinnPhong(shininess, dotNH);\n"
	"  return F * (G * D);\n"
    "  //return RECIPROCAL_PI * pow(dotNH, 120.0f) * specularColor;\n"
	"} // validated\n"

	"in vec3 vViewPosition;\n"

	"#ifndef FLAT_SHADED\n"
		"in vec3 vNormal;\n"
	"#endif\n"

	"float punctualLightIntensityToIrradianceFactor( const in float "
    "  lightDistance, const in float cutoffDistance, const in float "
    "  decayExponent ) {\n"
    "  if(cutoffDistance > 0.0 && decayExponent > 0.0) {\n"
    "    return pow(saturate(-lightDistance / cutoffDistance + 1.0), "
    "decayExponent);\n"
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

	"struct BlinnPhongMaterial {\n"
	"  vec3 diffuseColor;\n"
    "  vec3 specularColor;\n"
    "  float specularShininess;\n"
    "  float specularStrength;\n"
	"};\n"

	"void RE_Direct_BlinnPhong( const in IncidentLight directLight," 
	  "const in GeometricContext geometry, const in BlinnPhongMaterial material," 
	  "inout ReflectedLight reflectedLight ) {\n"
	"  float dotNL = saturate(dot(geometry.normal, directLight.direction));\n"
    "  vec3 irradiance = dotNL * directLight.color;\n"
    "#ifndef PHYSICALLY_CORRECT_LIGHTS\n"
    "  irradiance *= PI;  // punctual light\n"
    "#endif\n"
    "  reflectedLight.directDiffuse += irradiance * BRDF_Diffuse_Lambert(material.diffuseColor);\n"
    "  reflectedLight.directSpecular += irradiance * BRDF_Specular_BlinnPhong(directLight," 
	     "geometry, material.specularColor,material.specularShininess) * material.specularStrength;\n"
	"}\n"

	"void RE_IndirectDiffuse_BlinnPhong( const in vec3 irradiance, const in GeometricContext geometry,"
	  "const in BlinnPhongMaterial material, inout ReflectedLight reflectedLight ) {\n"
	"  reflectedLight.indirectDiffuse +=\n"
    "  irradiance * BRDF_Diffuse_Lambert(material.diffuseColor);\n"
	"}\n"
	
	"#define RE_Direct				RE_Direct_BlinnPhong\n"
	"#define RE_IndirectDiffuse RE_IndirectDiffuse_BlinnPhong\n"

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

	"  vec3 normal = normalize(vNormal);\n"
    "  //vec3 geometryNormal = normal;\n"
		
	"  float specularStrength;\n"
	"#ifdef USE_SPECULARMAP\n"
    "  vec4 texelSpecular = texture2D(specularMap, TexCoord);\n"
    "  specularStrength = texelSpecular.r;\n"
    "#else\n"
	"  specularStrength = 1.0;\n"
    "#endif\n"

	"  //accumulation\n"
    "  BlinnPhongMaterial material;\n"
    "  material.diffuseColor = diffuseColor.rgb;\n"
	"  material.specularColor = specular;\n"
	"  material.specularShininess = shininess;\n"
	"  material.specularStrength = specularStrength;\n"

	"  GeometricContext geometry;\n"
    "  geometry.position = -vViewPosition;\n"
    "  geometry.normal = normal;\n"
	"  geometry.viewDir = normalize(vViewPosition);\n"

	"  IncidentLight directLight;\n"

	"#if (NUM_POINT_LIGHTS > 0) && defined(RE_Direct)\n"

    "PointLight pointLight;\n"
	"#pragma unroll_loop_start\n"
    "for (int i = 0; i < NUM_POINT_LIGHTS; i++) {\n"
	"  pointLight = pointLights[i];\n"
    "  getPointDirectLightIrradiance(pointLight, geometry, directLight);\n"
	"  RE_Direct(directLight, geometry, material, reflectedLight);\n"
	"}\n"
	"#pragma unroll_loop_end\n"

	"#endif\n"

	"#if defined(RE_IndirectDiffuse)\n"
    "  vec3 iblIrradiance = vec3(0.0);\n"
	"  vec3 irradiance = getAmbientLightIrradiance(ambientLightColor);\n"
	"  //irradiance += getLightProbeIrradiance(lightProbe, geometry);\n"
	"#endif\n"

	"#if defined(RE_IndirectDiffuse)\n"
    "RE_IndirectDiffuse(irradiance, geometry, material, reflectedLight);\n"
	"#endif\n"
		  
    "  vec3 outgoingLight = reflectedLight.directDiffuse + reflectedLight.indirectDiffuse"
	  "+ reflectedLight.directSpecular + reflectedLight.indirectSpecular;\n"
    //"  vec3 outgoingLight = reflectedLight.directDiffuse + "
    //"reflectedLight.indirectDiffuse;\n"
   
	"  gl_FragColor = vec4(outgoingLight, diffuseColor.a);\n"

    "  //gl_FragColor = diffuseColor;\n"
    "}\n";
}