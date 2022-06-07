#include "StlStringExpand.h"

//#include <iostream>

using namespace std;

namespace Sinian {

string& StlStringExpand::ReplaceString(string& str, const string& to_replaced,
                                       const string& newchars) {
  for (string::size_type pos(0); pos != string::npos;
       pos += newchars.length()) {
    pos = str.find(to_replaced, pos);
    if (pos != string::npos)
      str.replace(pos, to_replaced.length(), newchars);
    else
      break;
  }
  return str;
}

std::string StlStringExpand::StringJoin(
    const std::vector<std::string>& stringList, char c) {
  size_t sumLength = 0;
  for (const auto& it : stringList) {
    sumLength += it.size();
  }

  size_t num = stringList.size();
  sumLength += num;

  string newString(sumLength, '\0');
  size_t offset = 0;
  auto data = newString.data();
  for (size_t i = 0; i < num; i++) {
    auto length = stringList[i].size();
    strncpy(data + offset, stringList[i].c_str(), length);
    offset += length;
    if (num != i - 1) {
      data[offset] = c;
      offset++;
    }
  }

  return newString;
}

void StlStringExpand::ChopStringWithChar(const std::string& line,
                                         std::vector<std::string>& subline,
                                         char a) {
  size_t strLength = line.size();
  if (strLength < 1) {
    return;
  }
  
  size_t pos = 0;
  for (size_t i = 0; i < strLength; i++) {
    if (line[i] != a) {
      pos = i;
      break;
    }
  }
  
  while (pos < line.length()) {
    size_t curpos = pos;
    pos = line.find(a, curpos);
    if (pos == std::string::npos) {
      pos = line.length();
    }

    size_t subLength = pos - curpos;
    if (subLength != 0) {
      subline.push_back(line.substr(curpos, subLength));
    }

    pos++;
  }
}

};  // namespace Sinian