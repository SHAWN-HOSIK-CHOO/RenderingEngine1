#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Model
{
public:
	Model(class Renderer* renderer);
	~Model();

	void ComputeWorldTransform();

	void AddMesh(class Mesh* mesh);
	void AddComponent(class Component* comp);
	void AddTexture(const std::string& filePath);

	void Unload();

	void Activate();
	void ActivateTexture(int index);

	void Draw();

	void Update(float deltaTime);
	void ProcessInput(const Uint8* state);

	//Getters && Setters
	void SetPosition(const glm::vec3& pos) { mPosition = pos; }
	glm::vec3& GetPosition() { return mPosition; }

	void SetRotation(const glm::quat& rot) { mRotation = rot; }
	glm::quat& GetRotation() { return mRotation; }

	void SetScale(const float scale) { mScale = glm::scale(glm::vec3(scale)); }
	glm::mat4& GetScale() { return mScale; }

	glm::mat4& GetWorldTransMatrix() { return mWorldTrans; }

	glm::vec3 GetForward() { return glm::toMat4(mRotation) * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f); }

	glm::vec3 GetRight() { return glm::toMat4(mRotation) * glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f); }

	class Mesh* GetMesh() { return mMesh; }

	class Renderer* GetRenderer() { return mOwner; }
private:
	glm::vec3 mPosition;
	glm::quat mRotation;
	glm::mat4 mScale;

	glm::mat4 mWorldTrans;

	class Mesh* mMesh;

	std::vector<class Component*> mComponents;

	std::vector<class Texture*> mTextures;

	class Renderer* mOwner;
};