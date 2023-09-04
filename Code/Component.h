#pragma once
#include <cstdint>
#include <SDL2/SDL.h>

class Component
{
public:
	Component(class Model* owner);
	virtual ~Component();

	virtual void Update(float deltaTime){}
	virtual void ProcessInput(const Uint8* state){}
protected:
	class Model* mOwner;
};