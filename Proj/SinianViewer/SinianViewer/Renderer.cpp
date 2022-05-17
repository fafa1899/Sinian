#include "Renderer.h"
#include "MaterialPropertie.h"
#include "MeshBasicMaterial.h"
#include "Program.h"
#include "ProgramParameters.h"
#include "Programs.h"
#include "ShaderObject.h"
#include "State.h"
#include "Textures.h"
#include "Uniform.h"
#include "UniformSetting.h"
#include "Uniforms.h"
#include "mesh.h"
#include "Properties.h"

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
    : programCache(make_shared<Programs>()),
      properties(make_shared<Properties>()),
      state(make_shared<State>()),
      textures(make_shared<Textures>(properties, state)),
      currentMaterialId(-1),
      currentCamera(nullptr) { 
}

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

void Renderer::Render(std::shared_ptr<Object3D> object,
                      std::shared_ptr<Camera> camera) {
  currentMaterialId = -1;
  currentCamera = nullptr;

  Clear();

  vector<shared_ptr<Mesh>> meshs;
  Object3DGetMeshs(object, meshs);

  for (size_t mi = 0; mi < meshs.size(); mi++) {
    std::map<std::string, std::any> uniforms;
    uniforms.emplace("projection", &(camera->ProjectionMatrix()));
    uniforms.emplace("view", &(camera->ViewMatrix()));
    uniforms.emplace("model", &(meshs[mi]->WorldModelMatrix()));

    // PrintMat(meshs[mi]->WorldModelMatrix());
    // cout << endl;

    std::shared_ptr<Material> material = meshs[mi]->MainMaterial();

    SetProgram(material, camera, meshs[mi]);

    // material->SetUniforms(uniforms);

    material->Update();

    meshs[mi]->Geometry()->Draw();
  }

  // cout << "------" << endl;
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
   
  if (material->Version() == materialPropertie->version) {
    // Todo:Other Condition
  } else {
    InitMaterial(materialPropertie, material);
    materialPropertie->version = material->Version();
  }

  bool refreshProgram = false;
  bool refreshMaterial = false;
  // bool refreshLights = false;

  std::shared_ptr<Program> program = materialPropertie->program;
  std::shared_ptr<Uniforms> p_uniforms = program->GetUniforms();
  std::map<std::string, UniformSetting>& m_uniforms =
      materialPropertie->shaderObject->uniforms;

  if (state->UseProgram(program->ProgramId())) {
    refreshProgram = true;
    refreshMaterial = true;
    // refreshLights = true;
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
      // refreshLights = true;    // remains set until update done
    }

    p_uniforms->SetValue("viewMatrix", camera->ViewMatrix());
  }

  if (refreshMaterial) {
    if (material->Type() == "MeshBasicMaterial") {
      RefreshUniformsCommon<MeshBasicMaterial>(
          materialPropertie->shaderObject->uniforms,
          static_pointer_cast<MeshBasicMaterial>(material));
    }
  }

  Uniforms::Upload(materialPropertie->uniformsList, m_uniforms, textures);

  // common matrices
  // p_uniforms->SetValue(_gl, 'modelViewMatrix', object.modelViewMatrix);
  // p_uniforms->SetValue(_gl, 'normalMatrix', object.normalMatrix);
  p_uniforms->SetValue("modelMatrix", object->WorldModelMatrix());
}

void Renderer::InitMaterial(
    std::shared_ptr<MaterialPropertie> materialPropertie,
    std::shared_ptr<Material> material) {
  //
  shared_ptr<ProgramParameters> parameters =
      programCache->GetParameters(material);
  string programCacheKey = programCache->GetProgramCacheKey(parameters);

  std::shared_ptr<Program> program = materialPropertie->program;
  bool programChange = true;

  if (!program) {
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

  Uniforms::SeqWithValue(progUniforms->Seq(),
                         parameters->shaderObject->uniforms,
                         materialPropertie->uniformsList);
}
}  // namespace Sinian
