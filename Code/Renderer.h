#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Renderer
{
public:
	Renderer(int width,int heght);
	~Renderer();

	bool Initialize();
	void Render();

	void SetRunning(bool sel) { mKeepRunning = sel; }
	bool KeepRunning() { return mKeepRunning; }

	bool CreateShader();
private:
	SDL_Window* mWindow;
	SDL_GLContext mContext;

	int mWidth;
	int mHeight;

	bool mKeepRunning;
	
	glm::mat4 mVP;
	glm::mat4 mView;
	glm::mat4 mProj;

	std::vector<class Model*> mModels;
	std::vector<class Mesh*>  mMeshes;

	//class Mesh* mCube;
	class VAO* mVertexArray;

	class Shader* mShader;
};