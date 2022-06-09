#include "Uniforms.h"
#include "Program.h"
#include "SingleUniform.h"
#include "StructuredUniform.h"
#include "Uniform.h"
#include "UniformSetting.h"

#include <glad/glad.h>
#include <iostream>

using namespace std;

namespace Sinian {
Uniforms::Uniforms(unsigned int program) {
  GLint n;
  glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &n);

  GLchar uniformName[256];
  GLsizei length;
  GLint size;
  GLenum type;

  for (int i = 0; i < n; i++) {
    glGetActiveUniform(program, i, sizeof(uniformName), &length, &size, &type,
                       uniformName);
    //cout << uniformName << '\t' << length << '\t' << size << '\t' << type
         //<< endl;
    GLint addr = glGetUniformLocation(program, uniformName);

    string strUniformName(uniformName);

    ParseUniform(strUniformName, type, addr);
  }
}

void Uniforms::ParseUniform(const std::string& uniformName, unsigned int type,
                            int addr) {
  size_t dotPos = uniformName.find('.');
  size_t bracketsPos = uniformName.find('[');

  if (dotPos != string::npos) {
    size_t length = dotPos;
    if (bracketsPos != string::npos && bracketsPos < dotPos) {
      length = bracketsPos;
    }
    string name = uniformName.substr(0, length);

    shared_ptr<StructuredUniform> uniformObject = nullptr;
    const auto& iter = map.find(name);
    if (iter == map.end()) {
      uniformObject = make_shared<StructuredUniform>(name);
      map[name] = uniformObject;
      seq.push_back(uniformObject);
    } else {
      uniformObject = static_pointer_cast<StructuredUniform>(iter->second);
    }

    uniformObject->SetUniform(uniformName, type, addr);
    // uniformObject->ShowUnifom();
  } else if (uniformName.find('[') != string::npos) {
    printf("Situations that cannot be handled:Uniforms-ParseUniform");
  } else {
    shared_ptr<SingleUniform> uniformObject = nullptr;

    switch (type) {
      case GL_FLOAT:
      case GL_FLOAT_VEC3:
      case GL_FLOAT_MAT3:
      case GL_FLOAT_MAT4:
      case GL_SAMPLER_2D: {
        uniformObject = make_shared<SingleUniform>(uniformName, addr, type);
        break;
      }
      default: {
        printf("No Support Uniform Type : %d!\n", type);
        break;
      }
    }

    if (uniformObject) {
      AddUniform(uniformObject);
    }
  }
}

void Uniforms::SeqWithValue(
    const std::vector<std::shared_ptr<Uniform>>& seq,
    const std::map<std::string, UniformSetting>& values,
    std::vector<std::shared_ptr<Uniform>>& outUniformsList) {
  //
  outUniformsList.clear();

  for (size_t i = 0, n = seq.size(); i != n; ++i) {
    std::shared_ptr<Uniform> u = seq[i];
    //cout << u->Id() << endl;
    auto it = values.find(u->Id());
    if (it != values.end()) {
      outUniformsList.push_back(u);
    }
  }
  //cout << endl;
}

void Uniforms::SetValue(std::string name, std::any value,
                        std::shared_ptr<Textures> textures) {
  const auto& iter = map.find(name);

  if (iter != map.end()) {
    iter->second->SetValue(value);
  }
}

void Uniforms::AddUniform(std::shared_ptr<Uniform> uniformObject) {
  // seq.push_back(uniformObject);
  // map[uniformObject->Id()] = uniformObject;

  const auto& id = uniformObject->Id();
  const auto& iter = map.find(id);
  if (iter == map.end()) {
    map[id] = uniformObject;
    seq.push_back(uniformObject);
  }
}

void Uniforms::Upload(const std::vector<std::shared_ptr<Uniform>>& seq,
                      const std::map<std::string, UniformSetting>& values,
                      std::shared_ptr<Textures> textures) {
  for (size_t i = 0, n = seq.size(); i != n; ++i) {
    std::shared_ptr<Uniform> u = seq[i];

    const auto& it = values.find(u->Id());
    if (it != values.end() && it->second.needsUpdate) {
      //cout << u->Id() << '\t' << it->second.value.type().name() << endl;  
      u->SetValue(it->second.value, textures);
    }

    // uniforms[].value = lights.State().ambient;
    // uniforms["pointLights"].value = lights.State().point;
  }
  //cout << endl;
}

}  // namespace Sinian