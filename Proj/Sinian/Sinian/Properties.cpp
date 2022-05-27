#include "Properties.h"
#include "MaterialPropertie.h"
#include "TexturePropertie.h"

#include <iostream>

using namespace std;

namespace Sinian {

template <typename Key, typename Prop>
static shared_ptr<Prop> GetProp(
    map<shared_ptr<Key>, shared_ptr<Prop>>& properties, shared_ptr<Key> key) {
  shared_ptr<Prop> propertie = nullptr;
  
  auto iter = properties.find(key);
  if (iter == properties.end()) {
    propertie = make_shared<Prop>();
    properties.emplace(key, propertie);
  } else {
    propertie = iter->second;
  }

  return propertie;
}

shared_ptr<MaterialPropertie> Properties::Get(
    std::shared_ptr<Material> material) {
  // shared_ptr<MaterialPropertie> materialPropertie = nullptr;
  // auto mIter = materialProperties.find(material);
  // if (mIter == materialProperties.end()) {
  //  materialPropertie = make_shared<MaterialPropertie>();
  //  materialProperties.emplace(material, materialPropertie);
  //} else {
  //  materialPropertie = mIter->second;
  //}

  // return materialPropertie;

  return GetProp<Material, MaterialPropertie>(materialProperties, material);
}

std::shared_ptr<TexturePropertie> Properties::Get(
    std::shared_ptr<Texture> texture) {
  return GetProp<Texture, TexturePropertie>(textureProperties, texture);
}

}  // namespace Sinian
