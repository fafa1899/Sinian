#ifndef CAPABILITIES_H
#define CAPABILITIES_H

namespace Sinian {

class Capabilities {
 public:
  ~Capabilities() {}
  Capabilities(const Capabilities&) = delete;
  Capabilities& operator=(const Capabilities&) = delete;
    
  static Capabilities& GetInstance();

  inline const int& MaxTextures() const { return maxTextures; }  
  
 private:
  Capabilities();

  int maxTextures;
};

}

#endif
