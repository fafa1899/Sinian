#include "Renderer.h"
#include "MaterialPropertie.h"
#include "Mesh.h"
#include "MeshBasicMaterial.h"
#include "MeshLambertMaterial.h"
#include "Program.h"
#include "ProgramParameters.h"
#include "Programs.h"
#include "Properties.h"
#include "RenderStateEx.h"
#include "RenderStatesEx.h"
#include "ShaderObject.h"
#include "State.h"
#include "Textures.h"
#include "Uniform.h"
#include "UniformSetting.h"
#include "Uniforms.h"

#include <iostream>

using namespace std;

namespace Sinian {
static std::shared_ptr<Mesh> Object3DGetMesh(std::shared_ptr<Object3D> object) {
  std::shared_ptr<Mesh> mesh = dynamic_pointer_cast<Mesh>(object);
  if (mesh) {
    return mesh;
  }
  return nullptr;
}

static void Object3DGetMeshs(std::shared_ptr<Object3D> object,
                             vector<shared_ptr<Mesh>>& materials) {
  shared_ptr<Mesh> material = Object3DGetMesh(object);
  if (material) {
    materials.push_back(material);
  }

  const auto& children = object->Children();
  for (const auto& iter : children) {
    Object3DGetMeshs(iter.second, materials);
  }
}

Renderer::Renderer()
    : currentRenderState(nullptr),
      state(make_shared<State>()),
      properties(make_shared<Properties>()),
      textures(make_shared<Textures>(properties, state)),
      programCache(make_shared<Programs>()),
      renderStates(make_shared<RenderStatesEx>()),
      currentMaterialId(-1),
      currentCamera(nullptr) {}

void Renderer::SetClearColor(const glm::vec4& color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::Clear(bool color, bool depth, bool stencil) {
  GLbitfield bits = 0;
  if (color) bits |= GL_COLOR_BUFFER_BIT;
  if (depth) bits |= GL_DEPTH_BUFFER_BIT;
  if (stencil) bits |= GL_STENCIL_BUFFER_BIT;
  glClear(bits);
}

// static void PrintMat(const glm::mat4& m)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			printf("%.9lf\t", m[i][j]);
//		}
//		printf("\n");
//	}
//}

void Renderer::SetSize(int width, int height) {
  state->Viewport(glm::vec4(0.0, 0.0, width, height));
}

void Renderer::ProjectObject(std::shared_ptr<Object3D> object) {
  // The actual type is already known, use static casts to save performance.
  if (object->Type() == "AmbientLight" || object->Type() == "PointLight") {
    currentRenderState->PushLight(static_pointer_cast<Light>(object));
  }

  const auto& children = object->Children();
  for (const auto& child : children) {
    ProjectObject(child.second);
  }
}

void Renderer::Render(std::shared_ptr<Scene> scene,
                      std::shared_ptr<Camera> camera) {
  currentMaterialId = -1;
  currentCamera = nullptr;

  Clear();

  currentRenderState = renderStates->Get(scene, camera);
  currentRenderState->Init();

  // Recursively traverse the scene tree to obtain the required data
  // information.
  ProjectObject(scene);

  currentRenderState->SetupLights(camera);

  vector<shared_ptr<Mesh>> meshs;
  Object3DGetMeshs(scene, meshs);

  for (size_t mi = 0; mi < meshs.size(); mi++) {
    std::map<std::string, std::any> uniforms;
    uniforms.emplace("projection", &(camera->ProjectionMatrix()));
    uniforms.emplace("view", &(camera->ViewMatrix()));
    uniforms.emplace("model", &(meshs[mi]->WorldModelMatrix()));

    // PrintMat(meshs[mi]->WorldModelMatrix());
    // cout << endl;

    std::shared_ptr<Material> material = meshs[mi]->MainMaterial();

    meshs[mi]->ModelViewMatrix(camera->ViewMatrix() *
                               meshs[mi]->WorldModelMatrix());

    glm::mat3 normalMatrix = glm::mat3(meshs[mi]->ModelViewMatrix());
    normalMatrix = glm::transpose(glm::inverse(normalMatrix));
    meshs[mi]->NormalMatrix(normalMatrix);

    SetProgram(material, camera, meshs[mi]);

    // material->SetUniforms(uniforms);

    material->Update();

    meshs[mi]->Geometry()->Draw();
  }

  currentRenderState = nullptr;
}

template <typename T>
void RefreshUniformsCommon(std::map<std::string, UniformSetting>& uniforms,
                           std::shared_ptr<T> material) {
  // uniforms.opacity.value = material.opacity;

  {
    const auto& it = uniforms.find("diffuse");
    if (it != uniforms.end()) {
      it->second.value = material->Color();
    }
  }

  {
    const auto& it = uniforms.find("map");
    if (it != uniforms.end()) {
      it->second.value = material->Map();
    }
  }
}

void Renderer::SetProgram(std::shared_ptr<Material> material,
                          std::shared_ptr<Camera> camera,
                          std::shared_ptr<Object3D> object) {
  //
  textures->ResetTextureUnits();

  // Get Current Material Propertie : Save Last Material
  shared_ptr<MaterialPropertie> materialPropertie = properties->Get(material);
  const Lights& lights = currentRenderState->GetLights();

  if (material->Version() == materialPropertie->version) {
    if (!materialPropertie->program) {
      InitMaterial(materialPropertie, material);
    } else if (materialPropertie->needsLights &&
               (materialPropertie->lightsStateVersion !=
                lights.State().version)) {
      InitMaterial(materialPropertie, material);
    }
  } else {
    InitMaterial(materialPropertie, material);
    materialPropertie->version = material->Version();
  }

  bool refreshProgram = false;
  bool refreshMaterial = false;
  bool refreshLights = false;

  std::shared_ptr<Program> program = materialPropertie->program;
  std::shared_ptr<Uniforms> p_uniforms = program->GetUniforms();
  std::map<std::string, UniformSetting>& m_uniforms =
      materialPropertie->shaderObject->uniforms;

  if (state->UseProgram(program->ProgramId())) {
    refreshProgram = true;
    refreshMaterial = true;
    refreshLights = true;
  }

  if (material->Id() != currentMaterialId) {
    currentMaterialId = material->Id();
    refreshMaterial = true;
  }

  if (refreshProgram || currentCamera != camera) {
    p_uniforms->SetValue("projectionMatrix", camera->ProjectionMatrix());

    if (currentCamera != camera) {
      currentCamera = camera;

      // lighting uniforms depend on the camera so enforce an update
      // now, in case this material supports lights - or later, when
      // the next material that does gets activated:

      refreshMaterial = true;  // set to true on material change
      refreshLights = true;    // remains set until update done
    }

    p_uniforms->SetValue("viewMatrix", camera->ViewMatrix());
  }

  if (refreshMaterial) {
    if (materialPropertie->needsLights) {
      // the current material requires lighting info

      // note: all lighting uniforms are always set correctly
      // they simply reference the renderer's state for their
      // values
      //
      // use the current material's .needsUpdate flags to set
      // the GL state when required

      MarkUniformsLightsNeedsUpdate(m_uniforms, refreshLights);

      // Todo:Each frame will have more than one value pass, which needs to be
      // optimized.
      std::map<std::string, UniformSetting>& uniforms =
          materialPropertie->shaderObject->uniforms;
      uniforms["ambientLightColor"].value = lights.State().ambient;
      uniforms["pointLights"].value = lights.State().point;
    }

    if (material->Type() == "MeshBasicMaterial") {
      RefreshUniformsCommon<MeshBasicMaterial>(
          m_uniforms, static_pointer_cast<MeshBasicMaterial>(material));
    } else if (material->Type() == "MeshLambertMaterial") {
      RefreshUniformsCommon<MeshLambertMaterial>(
          m_uniforms, static_pointer_cast<MeshLambertMaterial>(material));
      // refreshUniformsLambert(m_uniforms, material);
    }
  }

  Uniforms::Upload(materialPropertie->uniformsList, m_uniforms, textures);

  // common matrices
  p_uniforms->SetValue("modelViewMatrix", object->ModelViewMatrix());
  p_uniforms->SetValue("normalMatrix", object->NormalMatrix());
  p_uniforms->SetValue("modelMatrix", object->WorldModelMatrix());
}

void Renderer::InitMaterial(
    std::shared_ptr<MaterialPropertie> materialPropertie,
    std::shared_ptr<Material> material) {
  //
  const Lights& lights = currentRenderState->GetLights();

  const LightState& state = lights.State();
  int lightsStateVersion = state.version;

  //
  shared_ptr<ProgramParameters> parameters =
      programCache->GetParameters(material, state);
  string programCacheKey = programCache->GetProgramCacheKey(parameters);

  std::shared_ptr<Program> program = materialPropertie->program;
  bool programChange = true;

  if (!program) {
    // new material
  } else if (program->CacheKey() != programCacheKey) {
    // changed glsl or parameters
    programCache->ReleaseProgram(program);
  } else if (materialPropertie->lightsStateVersion != lightsStateVersion) {
    // change lightsState
    materialPropertie->lightsStateVersion = lightsStateVersion;
    programChange = false;
  } else if (!parameters->shaderID.empty()) {
    // same glsl and uniform list
    return;
  } else {
    programChange = false;
  }

  if (programChange) {
    std::shared_ptr<Program> program =
        programCache->AcquireProgram(parameters, programCacheKey);

    materialPropertie->program = program;
    materialPropertie->shaderObject = parameters->shaderObject;
    // material->program = program;
  }

  std::shared_ptr<Uniforms> progUniforms =
      materialPropertie->program->GetUniforms();

  // for (const auto& it : progUniforms->Seq()) {
  //  cout << it->Id() << endl;
  //}
  // cout << endl;

  std::map<std::string, UniformSetting>& uniforms =
      materialPropertie->shaderObject->uniforms;

  // store the light setup it was created for
  materialPropertie->needsLights = MaterialNeedsLights(material);
  materialPropertie->lightsStateVersion = lightsStateVersion;

  // Todo: Does not work The following update() is skipped.
  if (materialPropertie->needsLights) {
    // wire up the material to this renderer's lighting state
    uniforms["ambientLightColor"].value = state.ambient;
    uniforms["pointLights"].value = state.point;
  }

  Uniforms::SeqWithValue(progUniforms->Seq(),
                         parameters->shaderObject->uniforms,
                         materialPropertie->uniformsList);
}

bool Renderer::MaterialNeedsLights(std::shared_ptr<Material> material) {
  return material->Type() == "MeshLambertMaterial";
}

// If uniforms are marked as clean, they don't need to be loaded to the GPU.
void Renderer::MarkUniformsLightsNeedsUpdate(
    std::map<std::string, UniformSetting>& uniforms, bool value) {
  uniforms["ambientLightColor"].needsUpdate = value;
  uniforms["pointLights"].needsUpdate = value;
}

}  // namespace Sinian
