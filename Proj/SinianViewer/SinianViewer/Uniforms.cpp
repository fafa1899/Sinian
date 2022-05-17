#include "Uniforms.h"
#include "Program.h"
#include "SingleUniform.h"
#include "Uniform.h"
#include "UniformSetting.h"
//#include "Textures.h"

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
    // cout << uniformName << '\t' << length << '\t' << size << '\t' << type
    //<< endl;
    GLint addr = glGetUniformLocation(program, uniformName);

    shared_ptr<Uniform> uniformObject = nullptr;

    if (size == 1) {
      switch (type) {
        case GL_FLOAT:
        case GL_FLOAT_VEC3:
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
    } else {
      printf("Need StructuredUniform\n");
    }

    if (uniformObject) {
      AddUniform(uniformObject);
    }
  }

  // cout << seq.size() << '\t' << map.size() << endl;
}

void Uniforms::SeqWithValue(
    const std::vector<std::shared_ptr<Uniform>>& seq,
    const std::map<std::string, UniformSetting>& values,
    std::vector<std::shared_ptr<Uniform>>& outUniformsList) {
  //
  outUniformsList.clear();

  for (size_t i = 0, n = seq.size(); i != n; ++i) {
    std::shared_ptr<Uniform> u = seq[i];

    auto it = values.find(u->Id());
    if (it != values.end()) {
      outUniformsList.push_back(u);
    }
  }
}

void Uniforms::SetValue(std::string name, std::any value,
                        std::shared_ptr<Textures> textures) {
  const auto& iter = map.find(name);

  if (iter != map.end()) {
    iter->second->SetValue(value);
  }
}

void Uniforms::AddUniform(std::shared_ptr<Uniform> uniformObject) {
  seq.push_back(uniformObject);
  map[uniformObject->Id()] = uniformObject;
}

void Uniforms::Upload(const std::vector<std::shared_ptr<Uniform>>& seq,
                      const std::map<std::string, UniformSetting>& values,
                      std::shared_ptr<Textures> textures) {
  for (size_t i = 0, n = seq.size(); i != n; ++i) {
    std::shared_ptr<Uniform> u = seq[i];

    const auto& it = values.find(u->Id());
    if (it != values.end() && it->second.needsUpdate) {
      u->SetValue(it->second.value, textures);
    }
  }
}

}  // namespace Sinian