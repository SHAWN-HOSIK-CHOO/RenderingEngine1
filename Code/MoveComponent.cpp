#include "MoveComponent.h"
#include "Model.h"
#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include <cmath>

MoveComponent::MoveComponent(Model* model)
	:Component(model)
	,mForwardSpeed(0.0f)
	,mRotateSpeed(0.0f)
	,mStrafeSpeed(0.0f)
	,mKeys(nullptr)
{
	mKeys = mOwner->GetRenderer()->GetKeys();
}

void MoveComponent::Update(float deltaTime)
{
	
	if (!NearZero(mRotateSpeed))
	{
		glm::quat rot = mOwner->GetRotation();
		float angle = mRotateSpeed * deltaTime;
		glm::quat inc = glm::angleAxis(angle,glm::vec3(0.0f,1.0f,0.0f));
		rot = inc * rot;

		mOwner->SetRotation(rot);
	}
	
	if (!NearZero(mForwardSpeed))
	{
		glm::vec3 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		
		mOwner->SetPosition(pos);
	}
}

void MoveComponent::ProcessInput(const Uint8* state)
{
	/*
	if (state[SDL_SCANCODE_W])
	{
		mForwardSpeed += 0.4f;
		mRotateSpeed = 0.0f;
	}
	if (state[SDL_SCANCODE_S])
	{
		mForwardSpeed -= 0.4f;
		mRotateSpeed = 0.0f;
	}
	if (state[SDL_SCANCODE_D])
	{
		mRotateSpeed -= (glm::pi<float>()) / 5.0f;
		//mStrafeSpeed += 0.4f;
		mForwardSpeed = 0.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRotateSpeed += (glm::pi<float>()) / 5.0f;
		//mStrafeSpeed -= 0.4f;
		mForwardSpeed = 0.0f;
	}
	*/

	if (mKeys[SDLK_w])
	{
		mForwardSpeed += 0.4f;
	}
	if (mKeys[SDLK_s])
	{
		mForwardSpeed -= 0.4f;
	}
	if (mKeys[SDLK_d])
	{
		mRotateSpeed -= (glm::pi<float>()) / 5.0f;
	}
	if (mKeys[SDLK_a])
	{
		mRotateSpeed += (glm::pi<float>()) / 5.0f;
	}
}

bool MoveComponent::NearZero(float val, float epsilon)
{
	if (std::fabs(val) <= epsilon)
	{
		return true;
	}
	else
	{
		return false;
	}
}

