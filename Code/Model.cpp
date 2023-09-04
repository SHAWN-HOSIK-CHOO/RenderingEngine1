#include "Model.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "VAO.h"
#include <SDL2/SDL_log.h>

Model::Model(Renderer* renderer)
	:mPosition(glm::vec3(1.0f))
	, mRotation(glm::quat(glm::vec3(0.0f)))
	, mScale(glm::scale(glm::vec3(1.0f)))
	, mOwner(renderer)
	,mWorldTrans(glm::mat4(1.0f))
	,mMesh(nullptr)
{

}
Model::~Model()
{
	Unload();
}

void Model::ComputeWorldTransform()
{
	glm::mat4 T = glm::translate(glm::mat4(1.0f),mPosition);
	glm::mat4 R = glm::toMat4(mRotation);
	glm::mat4 S = mScale;

	mWorldTrans = T * R * S;
}

void Model::AddMesh(Mesh* mesh)
{
	mMesh = mesh;
}

void Model::Unload()
{
	delete mMesh;
}

void Model::Activate()
{
	mMesh->Activate();
}

void Model::Draw()
{
	mMesh->Draw();
}