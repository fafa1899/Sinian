#ifndef STLSTRINGEXPAND_HPP
#define STLSTRINGEXPAND_HPP

#include "SinianApi.h"

#include <string>
#include <vector>

namespace Sinian {

class SINIAN_API StlStringExpand {
 public:
  // Find old string and replace with new string
  static std::string& ReplaceString(std::string& str,
                                    const std::string& to_replaced,
                                    const std::string& newchars);

  static std::string StringJoin(const std::vector<std::string>& stringList,
                                char c);

  //Divide the string according to the character
  static void ChopStringWithChar(const std::string& line,
                                        std::vector<std::string>& subline,
                                        char a);
};

}  // namespace Sinian

#endif
