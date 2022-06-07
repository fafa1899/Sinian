#include "RenderStatesEx.h"
#include "Camera.h"
#include "RenderStateEx.h"
#include "Scene.h"

using namespace std;

namespace Sinian {

shared_ptr<RenderStateEx> RenderStatesEx::Get(shared_ptr<Scene> scene,
                                              shared_ptr<Camera> camera) {
  // begin
  shared_ptr<RenderStateEx> renderState = nullptr;

  auto iter = renderStates.find(scene);
  if (iter == renderStates.end()) {
    renderState = make_shared<RenderStateEx>();
    renderStates[scene][camera] = renderState;

    // scene.addEventListener('dispose', onSceneDispose);

  } else {
    auto& tmp = renderStates[scene];
    const auto& it = tmp.find(camera);
    if (it == tmp.end()) {
      renderState = make_shared<RenderStateEx>();
      tmp[camera] = renderState;
    } else {
      renderState = it->second;
    }
  }

  return renderState;
}

}  // namespace Sinian