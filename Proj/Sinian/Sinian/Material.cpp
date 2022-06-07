#include "Material.h"
#include "Texture2D.h"

#include <iostream>

using namespace std;

namespace Sinian {

int Material::materialId = 0;

Material::Material()
    : type("Material"), id(materialId++), version(0), needsUpdate(false) {}

Material::~Material() {}

void Material::NeedsUpdate(bool value) {
  if (value) {
    version++;
  }
}

void Material::Update() {
  for (unsigned int ti = 0; ti < textures.size(); ti++) {
    glActiveTexture(GL_TEXTURE0 +
                    ti);  // active proper texture unit before binding
    glBindTexture(GL_TEXTURE_2D, textures[ti]->Id());
  }

  renderState.Apply();
}

//void Material::SetUniform(const std::string& name, std::any value) {
//  shader.Use();  // don't forget to activate/use the shader before setting
//                 // uniforms!
//  SetUniformValue(name, value);
//}

//void Material::SetUniforms(const std::map<std::string, std::any>& uniforms) {
//  shader.Use();  // don't forget to activate/use the shader before setting
//                 // uniforms!
//  for (const auto& iter : uniforms) {
//    SetUniformValue(iter.first, iter.second);
//  }
//}

//void Material::SetUniformValue(const std::string& name, std::any value) {
//  if (typeid(shared_ptr<Texture2D>) == value.type()) {
//    auto iter = textureNameAndTextureUnit.find(name);
//    if (textureNameAndTextureUnit.end() == iter) {
//      int unitId = static_cast<int>(textures.size());
//      shader.SetUniform(name, unitId);
//      textureNameAndTextureUnit.emplace(name, unitId);
//      textures.push_back(any_cast<shared_ptr<Texture2D>>(value));
//    } else {
//      shader.SetUniform(name, iter->second);
//    }
//  } else {
//    shader.SetUniform(name, value);
//  }
//}

}  // namespace Sinian