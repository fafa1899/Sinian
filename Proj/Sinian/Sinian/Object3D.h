#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "SinianApi.h"

#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <vector>

namespace Sinian {

class SINIAN_API Object3D : public std::enable_shared_from_this<Object3D> {
 public:
  Object3D(std::shared_ptr<Object3D> parent = nullptr);
  virtual ~Object3D();

  inline const int& Id() const { return id; }

  inline const std::string& Type() const { return type; }

  inline const std::string& Uuid() const { return uuid; }
  inline const std::map<std::string, std::shared_ptr<Object3D>>& Children()
      const {
    return children;
  }
  void Parent(std::shared_ptr<Object3D> parent);

  void Add(std::shared_ptr<Object3D> object);
  // remove
  // clear

  // inline const glm::mat4& ParentModelMatrix() { return parentModelMatrix; }

  // Position
  inline const glm::vec3& WorldPosition() const { return worldPosition; }
  void WorldPosition(const glm::vec3& position);
  void WorldPosition(float x, float y, float z) {
    WorldPosition(glm::vec3(x, y, z));
  }

  inline const glm::vec3& LocalPosition() const { return localPosition; }
  void LocalPosition(const glm::vec3& position);
  void LocalPosition(float x, float y, float z) {
    LocalPosition(glm::vec3(x, y, z));
  }

  // Euler
  inline const glm::vec3& WorldEulerAngles() const { return worldEulerAngles; }
  void WorldEulerAngles(const glm::vec3& euler);
  void WorldEulerAngles(float x, float y, float z) {
    WorldEulerAngles(glm::vec3(x, y, z));
  }

  inline const glm::vec3& LocalEulerAngles() const { return localEulerAngles; }
  void LocalEulerAngles(const glm::vec3& euler);
  void LocalEulerAngles(float x, float y, float z) {
    WorldEulerAngles(glm::vec3(x, y, z));
  }

  // Scale
  inline const glm::vec3& LocalScale() const { return localScale; }
  void LocalScale(const glm::vec3& scale);
  void LocalScale(float x, float y, float z) { LocalScale(glm::vec3(x, y, z)); }

  //
  inline const glm::vec3& WorldScale() const { return worldScale; }

  // WorldModel
  void WorldModelTranform(const glm::vec3& position, const glm::vec3& euler);

  // The global transform of the object. If the Object3D has no parent, then
  // it's identical to the local transform matrix.
  const glm::mat4& WorldModelMatrix() const { return worldModelMatrix; }
  const glm::mat4& WorldModelMatrixInverse() const {
    return worldModelMatrixInverse;
  }

  // LocalModel
  void LocalModelTranform(const glm::vec3& position, const glm::vec3& euler);
  void LocalModelTranform(const glm::vec3& position, const glm::vec3& euler,
                          const glm::vec3& scale);

  void LookAt(const glm::vec3& eye, const glm::vec3& center,
              glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));

  const glm::vec3& Front() { return front; }
  const glm::vec3& Up() { return up; }
  const glm::vec3& Right() { return right; }

  // This is passed to the shader and used to calculate the position of the
  // object.
  const glm::mat4& ModelViewMatrix() const { return modelViewMatrix; }
  void ModelViewMatrix(const glm::mat4& modelViewMatrix) {
    this->modelViewMatrix = modelViewMatrix;
  }

  // This is passed to the shader and used to calculate lighting for the object.
  // It is the transpose of the inverse of the upper left 3x3 sub-matrix of this
  // object's modelViewMatrix.
  const glm::mat3& NormalMatrix() const { return normalMatrix; }
  void NormalMatrix(const glm::mat3& normalMatrix) {
    this->normalMatrix = normalMatrix;
  }
  
 protected:
  void CalculateChildrenWorld();

  void UpdateWorldFromParent();
  void UpdateLocalFromParent();

  void UpdateLocalModelFromTRS();
  void UpdateWorldModelFromTRS();

  static int object3DId;

  int id;
  std::string type;

  std::string uuid;
  std::shared_ptr<Object3D> parent;
  std::map<std::string, std::shared_ptr<Object3D>> children;

  glm::mat4 worldTranslationMatrix;
  glm::mat4 worldRotationMatrix;
  glm::mat4 worldScaleMatrix;
  glm::mat4 worldModelMatrix;

  glm::mat4 worldTranslationMatrixInverse;
  glm::mat4 worldRotationMatrixInverse;
  glm::mat4 worldScaleMatrixInverse;
  glm::mat4 worldModelMatrixInverse;

  glm::mat4 localTranslationMatrix;
  glm::mat4 localRotationMatrix;
  glm::mat4 localScaleMatrix;
  glm::mat4 localModelMatrix;

  glm::mat4 localTranslationMatrixInverse;
  glm::mat4 localRotationMatrixInverse;
  glm::mat4 localScaleMatrixInverse;
  glm::mat4 localModelMatrixInverse;

  glm::vec3 worldPosition;
  glm::vec3 worldEulerAngles;  // Y * X *Z order
  glm::vec3 worldScale;

  glm::vec3 localPosition;
  glm::vec3 localEulerAngles;
  glm::vec3 localScale;

  glm::vec3 front;  // Front Vector In World Space
  glm::vec3 up;     // Up Vector of View Coordinate System in World Space
  glm::vec3 right;  // Right Vector In World Space

  glm::mat4 modelViewMatrix;
  glm::mat3 normalMatrix;
};

}  // namespace Sinian

#endif
