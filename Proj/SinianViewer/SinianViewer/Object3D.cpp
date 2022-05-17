#include "Object3D.h"
#include "Uuid.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

using namespace std;

namespace Sinian
{
	Object3D::Object3D(std::shared_ptr<Object3D> p):		
		uuid(Uuid::Generate()),
		parent(p),
		worldTranslationMatrix(1.0f),
		worldRotationMatrix(1.0f),
		worldScaleMatrix(1.0f),
		worldModelMatrix(1.0f),
		worldTranslationMatrixInverse(1.0f),
		worldRotationMatrixInverse(1.0f),
		worldScaleMatrixInverse(1.0f),
		worldModelMatrixInverse(1.0f),
		localTranslationMatrix(1.0f),
		localRotationMatrix(1.0f),
		localScaleMatrix(1.0f),
		localModelMatrix(1.0f),
		localTranslationMatrixInverse(1.0f),
		localRotationMatrixInverse(1.0f),
		localScaleMatrixInverse(1.0f),
		localModelMatrixInverse(1.0f),
		worldPosition(0.0f, 0.0f, 0.0f),
		worldEulerAngles(0.0f, 0.0f, 0.0f),
		worldScale(1.0f, 1.0f, 1.0f),
		localPosition(0.0f, 0.0f, 0.0f),
		localEulerAngles(0.0f, 0.0f, 0.0f),
		localScale(1.0f, 1.0f, 1.0f)
		//parentPosition(0.0f, 0.0f, 0.0f),
		//parentModelMatrix(1.0f)
	{		
	}

	//ToDO:Release SubNode is Need
	Object3D::~Object3D()
	{
	}

	//static void PrintMat(const glm::mat4& m)
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		for (int j = 0; j < 4; j++)
	//		{
	//			printf("%.9lf\t", m[i][j]);
	//		}
	//		printf("\n");
	//	}
	//}
	
	void Object3D::Add(std::shared_ptr<Object3D> object)
	{
		object->Parent(shared_from_this());
		children.emplace(object->Uuid(), object);
	}

	void Object3D::Parent(std::shared_ptr<Object3D> parent)
	{
		this->parent = parent;
		this->UpdateWorldFromParent();
		this->CalculateChildrenWorld();
	}

	void Object3D::CalculateChildrenWorld()
	{
		for (const auto &child : children)
		{
			child.second->UpdateWorldFromParent();
			child.second->CalculateChildrenWorld();
		}
	}


	void Object3D::UpdateWorldFromParent()
	{
		worldModelMatrix = parent->WorldModelMatrix() * localModelMatrix;
		worldModelMatrixInverse = localModelMatrixInverse * parent->WorldModelMatrixInverse();

		glm::quat quaternion;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(worldModelMatrix, worldScale, quaternion, worldPosition, skew, perspective);

		//
		worldTranslationMatrix = glm::translate(glm::identity<glm::mat4>(), worldPosition);
		worldTranslationMatrixInverse = glm::translate(glm::identity<glm::mat4>(), -worldPosition);

		//
		worldRotationMatrix = glm::toMat4(quaternion);
		worldRotationMatrixInverse = glm::transpose(worldRotationMatrix);
		glm::extractEulerAngleYXZ(worldRotationMatrix, worldEulerAngles.y, worldEulerAngles.x, worldEulerAngles.z);
		right = worldRotationMatrix[0];
		up = worldRotationMatrix[1];
		front = worldRotationMatrix[2];

		//
		worldScaleMatrix = glm::scale(glm::identity<glm::mat4>(), worldScale);
		worldScaleMatrixInverse = glm::scale(glm::identity<glm::mat4>(), 1.0f / worldScale);
	}

	void Object3D::UpdateLocalFromParent()
	{
		localModelMatrix = parent->WorldModelMatrixInverse() * worldModelMatrix;
		localModelMatrixInverse = worldModelMatrixInverse * parent->WorldModelMatrix();

		glm::quat quaternion;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(localModelMatrix, localScale, quaternion, localPosition, skew, perspective);

		//
		localTranslationMatrix = glm::translate(glm::identity<glm::mat4>(), localPosition);
		localTranslationMatrixInverse = glm::translate(glm::identity<glm::mat4>(), -localPosition);

		//
		localRotationMatrix = glm::toMat4(quaternion);
		localRotationMatrixInverse = glm::transpose(localRotationMatrix);
		glm::extractEulerAngleYXZ(localRotationMatrix, localEulerAngles.y, localEulerAngles.x, localEulerAngles.z);

		//
		localScaleMatrix = glm::scale(glm::identity<glm::mat4>(), localScale);
		localScaleMatrixInverse = glm::scale(glm::identity<glm::mat4>(), 1.0f / localScale);
	}

	void Object3D::UpdateLocalModelFromTRS()
	{
		localModelMatrix = localTranslationMatrix * localRotationMatrix * localScaleMatrix;		
		localModelMatrixInverse = localScaleMatrixInverse * localRotationMatrixInverse * localTranslationMatrixInverse;		
	}

	void Object3D::UpdateWorldModelFromTRS()
	{
		worldModelMatrix = worldTranslationMatrix * worldRotationMatrix * worldScaleMatrix;
		worldModelMatrixInverse = worldScaleMatrixInverse * worldRotationMatrixInverse * worldTranslationMatrixInverse;
	}

	void Object3D::WorldPosition(const glm::vec3& position)
	{
		worldPosition = position;
		worldTranslationMatrix = glm::translate(glm::identity<glm::mat4>(), worldPosition);
		worldTranslationMatrixInverse = glm::translate(glm::identity<glm::mat4>(), -worldPosition);
		
		UpdateWorldModelFromTRS();

		if (parent)
		{
			UpdateLocalFromParent();
		}
		else
		{
			localPosition = worldPosition;
			localTranslationMatrix = worldTranslationMatrix;
			localTranslationMatrixInverse = worldTranslationMatrixInverse;

			localModelMatrix = worldModelMatrix;
			localModelMatrixInverse = worldModelMatrixInverse;
		}
	}

	void Object3D::LocalPosition(const glm::vec3& position)
	{
		localPosition = position;
		localTranslationMatrix = glm::translate(glm::identity<glm::mat4>(), localPosition);
		localTranslationMatrixInverse = glm::translate(glm::identity<glm::mat4>(), -localPosition);

		UpdateLocalModelFromTRS();

		if (parent)
		{
			UpdateWorldFromParent();
		}
		else
		{
			worldPosition = localPosition;
			worldTranslationMatrix = localTranslationMatrix;
			worldTranslationMatrixInverse = localTranslationMatrixInverse;

			worldModelMatrix = localModelMatrix;
			worldModelMatrixInverse = localModelMatrixInverse;
		}
	}

	void Object3D::WorldEulerAngles(const glm::vec3& euler)
	{
		worldEulerAngles = euler;
		worldRotationMatrix = glm::eulerAngleYXZ(euler.y, euler.x, euler.z);
		worldRotationMatrixInverse = glm::transpose(worldRotationMatrix);

		UpdateWorldModelFromTRS();
				
		right = worldRotationMatrix[0];
		up = worldRotationMatrix[1];
		front = worldRotationMatrix[2];
		
		if (parent)
		{
			UpdateLocalFromParent();
		}
		else
		{
			localEulerAngles = worldEulerAngles;
			localRotationMatrix = worldRotationMatrix;
			localRotationMatrixInverse = worldRotationMatrixInverse;

			localModelMatrix = worldModelMatrix;
			localModelMatrixInverse = worldModelMatrixInverse;			
		}
	}

	void Object3D::LocalEulerAngles(const glm::vec3& euler)
	{
		localEulerAngles = euler;
		localRotationMatrix = glm::eulerAngleYXZ(euler.y, euler.x, euler.z);
		localRotationMatrixInverse = glm::transpose(localRotationMatrix);

		UpdateLocalModelFromTRS();

		if (parent)
		{
			UpdateWorldFromParent();
		}
		else
		{
			worldEulerAngles = localEulerAngles;
			worldRotationMatrix = localRotationMatrix;
			worldRotationMatrixInverse = localRotationMatrixInverse;

			worldModelMatrix = localModelMatrix;
			worldModelMatrixInverse = localModelMatrixInverse;
		}

		right = worldRotationMatrix[0];
		up = worldRotationMatrix[1];
		front = worldRotationMatrix[2];		
	}

	void Object3D::LocalScale(const glm::vec3& scale)
	{
		localScale = scale;
		localRotationMatrix = glm::scale(glm::identity<glm::mat4>(), localScale);
		localRotationMatrixInverse = glm::scale(glm::identity<glm::mat4>(), 1.0f / localScale);

		UpdateLocalModelFromTRS();

		if (parent)
		{
			UpdateWorldFromParent();
		}
		else
		{
			worldScale = localScale;
			worldScaleMatrix = localScaleMatrix;
			worldScaleMatrixInverse = localScaleMatrixInverse;

			worldModelMatrix = localModelMatrix;
			worldModelMatrixInverse = localModelMatrixInverse;
		}
	}

	void Object3D::WorldModelTranform(const glm::vec3& position, const glm::vec3& euler)
	{
		worldPosition = position;
		worldTranslationMatrix = glm::translate(glm::identity<glm::mat4>(), worldPosition);
		worldTranslationMatrixInverse = glm::translate(glm::identity<glm::mat4>(), -worldPosition);

		worldEulerAngles = euler;
		worldRotationMatrix = glm::eulerAngleYXZ(euler.y, euler.x, euler.z);
		worldRotationMatrixInverse = glm::transpose(worldRotationMatrix);
		right = worldRotationMatrix[0];
		up = worldRotationMatrix[1];
		front = worldRotationMatrix[2];
		
		UpdateWorldModelFromTRS();

		if (parent)
		{
			UpdateLocalFromParent();
		}
		else
		{
			localPosition = worldPosition;
			localTranslationMatrix = worldTranslationMatrix;
			localTranslationMatrixInverse = worldTranslationMatrixInverse;

			localEulerAngles = worldEulerAngles;
			localRotationMatrix = worldRotationMatrix;
			localRotationMatrixInverse = worldRotationMatrixInverse;

			localModelMatrix = worldModelMatrix;
			localModelMatrixInverse = worldModelMatrixInverse;
		}
	}

	void Object3D::LocalModelTranform(const glm::vec3& position, const glm::vec3& euler)
	{
		localPosition = position;
		localTranslationMatrix = glm::translate(glm::identity<glm::mat4>(), localPosition);
		localTranslationMatrixInverse = glm::translate(glm::identity<glm::mat4>(), -localPosition);

		localEulerAngles = euler;
		localRotationMatrix = glm::eulerAngleYXZ(euler.y, euler.x, euler.z);
		localRotationMatrixInverse = glm::transpose(localRotationMatrix);

		UpdateLocalModelFromTRS();
		
		if (parent)
		{
			UpdateWorldFromParent();
		}
		else
		{
			worldPosition = localPosition;
			worldTranslationMatrix = localTranslationMatrix;
			worldTranslationMatrixInverse = localTranslationMatrixInverse;

			worldEulerAngles = localEulerAngles;
			worldRotationMatrix = localRotationMatrix;
			worldRotationMatrixInverse = localRotationMatrixInverse;

			worldModelMatrix = localModelMatrix;
			worldModelMatrixInverse = localModelMatrixInverse;
		}

		right = worldRotationMatrix[0];
		up = worldRotationMatrix[1];
		front = worldRotationMatrix[2];
	}

	void Object3D::LocalModelTranform(const glm::vec3& position, const glm::vec3& euler, const glm::vec3& scale)
	{
		localPosition = position;
		localTranslationMatrix = glm::translate(glm::identity<glm::mat4>(), localPosition);
		localTranslationMatrixInverse = glm::translate(glm::identity<glm::mat4>(), -localPosition);

		localEulerAngles = euler;
		localRotationMatrix = glm::eulerAngleYXZ(euler.y, euler.x, euler.z);
		localRotationMatrixInverse = glm::transpose(localRotationMatrix);

		localScale = scale;
		localRotationMatrix = glm::scale(glm::identity<glm::mat4>(), localScale);
		localRotationMatrixInverse = glm::scale(glm::identity<glm::mat4>(), 1.0f / localScale);

		UpdateLocalModelFromTRS();
	
		if (parent)
		{
			UpdateWorldFromParent();		
		}
		else
		{
			worldPosition = localPosition;
			worldTranslationMatrix = localTranslationMatrix;
			worldTranslationMatrixInverse = localTranslationMatrixInverse;

			worldEulerAngles = localEulerAngles;
			worldRotationMatrix = localRotationMatrix;
			worldRotationMatrixInverse = localRotationMatrixInverse;

			worldScale = localScale;
			worldScaleMatrix = localScaleMatrix;
			worldScaleMatrixInverse = localScaleMatrixInverse;

			worldModelMatrix = localModelMatrix;
			worldModelMatrixInverse = localModelMatrixInverse;
		}

		right = worldRotationMatrix[0];
		up = worldRotationMatrix[1];
		front = worldRotationMatrix[2];
	}

	void Object3D::LookAt(const glm::vec3& eye, const glm::vec3& center, glm::vec3 worldUp)
	{
		//glm::vec3 d = eye - center;
		front = normalize(eye - center);
		right = glm::normalize(glm::cross(worldUp, front));
		up = glm::cross(front, right);

		worldModelMatrix = glm::mat4(1.0f);
		worldModelMatrix[0][0] = right.x;
		worldModelMatrix[0][1] = right.y;
		worldModelMatrix[0][2] = right.z;
		worldModelMatrix[1][0] = up.x;
		worldModelMatrix[1][1] = up.y;
		worldModelMatrix[1][2] = up.z;
		worldModelMatrix[2][0] = front.x;
		worldModelMatrix[2][1] = front.y;
		worldModelMatrix[2][2] = front.z;
		worldModelMatrix[3][0] = eye.x;
		worldModelMatrix[3][1] = eye.y;
		worldModelMatrix[3][2] = eye.z;
		//PrintMat(worldModelMatrix);
		//
		////worldModelMatrix = glm::lookAt(eye, center, worldUp);
		//
		//worldEulerAngles.y = 0;
		//worldEulerAngles.x = 0;
		//worldEulerAngles.z = 0;
		//glm::extractEulerAngleZXY(worldModelMatrix, worldEulerAngles.z, worldEulerAngles.x, worldEulerAngles.y);
		//cout << glm::degrees(worldEulerAngles.z) << '\t' << glm::degrees(worldEulerAngles.x) << '\t' << glm::degrees(worldEulerAngles.y) << endl;

		//float ry = atan(front.z / front.x);
		//float rx = asin(front.y);
		//cout << glm::degrees(ry) << '\t' << glm::degrees(rx) << endl;

		//cout << endl;
		//glm::mat4 r = glm::eulerAngleXY(rx, ry);
		//PrintMat(r);

		worldPosition = eye;


		//glm::yawPitchRoll();
	}
}

