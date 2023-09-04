#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

class Model
{
public:
	Model(class Renderer* renderer);
	~Model();

	void ComputeWorldTransform();

	void AddMesh(class Mesh* mesh);

	void Unload();

	void Activate();

	void Draw();
	//Getters && Setters
	void SetPosition(glm::vec3& pos) { mPosition = pos; }
	glm::vec3& GetPosition() { return mPosition; }

	void SetRotation(glm::quat& rot) { mRotation = rot; }
	glm::quat& GetRotation() { return mRotation; }

	void SetScale(float scale) { mScale = glm::scale(glm::vec3(scale)); }
	glm::mat4& GetScale() { return mScale; }

	class Mesh* GetMesh() { return mMesh; }
private:
	glm::vec3 mPosition;
	glm::quat mRotation;
	glm::mat4 mScale;

	glm::mat4 mWorldTrans;

	class Mesh* mMesh;

	class Renderer* mOwner;
};