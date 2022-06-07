// StringTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <StlStringExpand.h>

using namespace std;
using namespace Sinian;

int main() {
  //std::string line = ",,,11111,2222,,3333,,4444,,,";
  //std::string line = "      aaaaa      bbb      cccc     ddd        ";
  std::string line = "fafafawf";
  std::vector<std::string> subline;
  char a = ' ';

  StlStringExpand::ChopStringWithChar(line, subline, a);

  cout << subline.size() << endl; 
  for (auto it : subline) {
    cout << it << endl;
  }

  return 1;
}
