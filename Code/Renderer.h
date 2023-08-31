#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

class Renderer
{
public:
	Renderer(int width,int heght);
	~Renderer();

	bool Initialize();
	void Render();
	void CreateVAO(const float* v,unsigned int nv,const unsigned int* i,unsigned int ni);

	void SetRunning(bool sel) { mKeepRunning = sel; }
	bool KeepRunning() { return mKeepRunning; }
private:
	SDL_Window* mWindow;
	SDL_GLContext mContext;

	class VAO* mVertexArray;

	int mWidth;
	int mHeight;

	bool mKeepRunning;
};