#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Model* model);

	void Update(float deltaTime) override;
	void ProcessInput(const Uint8* state) override;

	float GetForwardSpeed() { return mForwardSpeed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

	float GetRotateSpeed() { return mForwardSpeed; }
	void SetRotateSpeed(float speed) { mRotateSpeed = speed; }

	bool NearZero(float val,float epsilon = 0.001f);
private:
	float mForwardSpeed;
	float mRotateSpeed;
	float mStrafeSpeed;
};