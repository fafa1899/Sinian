#ifndef SINIAN_RENDERSTATEEXS_H
#define SINIAN_RENDERSTATEExS_H

#include <map>
#include <memory>

namespace Sinian {

class RenderStateEx;
class Scene;
class Camera;

//Todo: �����Camera��Scene����Դ�������ͷ�ʱ��Ҫremove������Ժ���Ҫ������
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