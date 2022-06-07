#include "StructuredUniform.h"
#include "SingleUniform.h"
#include "StlStringExpand.h"
#include "UniformSetting.h"

#include <iostream>
#include <map>
#include <string>

using namespace std;

namespace Sinian {

void StructuredUniform::SetValue(const std::any& v,
                                 std::shared_ptr<Textures> textures) {
  for (size_t i = 0, n = seq.size(); i < n; i++) {
    if (seq[i]->ClassName() == "StructuredUniform") {
      shared_ptr<StructuredUniform> uniform =
          static_pointer_cast<StructuredUniform>(seq[i]);
      const auto &uniformList = any_cast<vector<std::map<string, UniformSetting>>>(v);
      seq[i]->SetValue(uniformList[i]);
    } else if (seq[i]->ClassName() == "SingleUniform") {
      const auto& uniforms = any_cast<std::map<string, UniformSetting>>(v);
      const auto& iter = uniforms.find(seq[i]->Id());      
      if (iter != uniforms.end()) {
        //cout << iter->first << '\t' << iter->second.value.type().name() << endl;
		seq[i]->SetValue(iter->second.value, textures);
      }
    }
  }
}

void StructuredUniform::SetUniform(const std::string& fullName,
                                   unsigned int type, int addr) {
  // Recursively insert StructuredUniform child nodes until the last leaf node
  // is SingleUniform.
  size_t pos = fullName.find('.');
  if (pos == string::npos) {
    shared_ptr<SingleUniform> uniformOject =
        make_shared<SingleUniform>(fullName, addr, type);
    AddUniform(uniformOject);
  } else {
    const string& firstName = fullName.substr(0, pos);
    const string& secondName =
        fullName.substr(pos + 1, fullName.size() - pos - 1);

    //
    size_t startPos = firstName.find('[');
    size_t endPos = firstName.find(']');

    // Array as a layer of StructuredUniform
    string name = "0";
    if (startPos != string::npos && endPos != string::npos &&
        endPos > startPos + 1) {
      name = firstName.substr(startPos + 1, endPos - startPos - 1);
    }

    shared_ptr<StructuredUniform> child = nullptr;
    // cout << name << endl;
    const auto& iter = map.find(name);
    if (iter != map.end()) {
      child = static_pointer_cast<StructuredUniform>(iter->second);
    } else {
      child = make_shared<StructuredUniform>(name);
      AddUniform(child);
    }
    child->SetUniform(secondName, type, addr);
  }
}

void StructuredUniform::AddUniform(std::shared_ptr<Uniform> uniformObject) {
  const auto& id = uniformObject->Id();
  const auto& iter = map.find(id);
  if (iter == map.end()) {
    map[id] = uniformObject;
    seq.push_back(uniformObject);
  }
}

void StructuredUniform::ShowUnifom() {
  // cout << map.size() << endl;
  for (const auto& it : map) {
    // cout << it.first << endl;
    if (typeid(*it.second) == typeid(StructuredUniform)) {
      shared_ptr<StructuredUniform> uniform =
          static_pointer_cast<StructuredUniform>(it.second);
      uniform->ShowUnifom();
    }
  }
}

}  // namespace Sinian