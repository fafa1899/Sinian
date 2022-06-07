#ifndef SINIAN_RENDERSTATEEXS_H
#define SINIAN_RENDERSTATEExS_H

#include <map>
#include <memory>

namespace Sinian {

class RenderStateEx;
class Scene;
class Camera;

//Todo: 存放了Camera和Scene的资源，在其释放时需要remove。这个以后需要修正。
class RenderStatesEx {
 public:
  std::shared_ptr<RenderStateEx> Get(std::shared_ptr<Scene> scene,
                                     std::shared_ptr<Camera> camera);

 private:
  std::map<std::shared_ptr<Scene>,
           std::map<std::shared_ptr<Camera>, std::shared_ptr<RenderStateEx>>>
      renderStates;
};

}  // namespace Sinian

#endif