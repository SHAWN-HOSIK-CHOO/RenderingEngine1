#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_map>

class Renderer
{
public:
	Renderer(int width,int heght);
	~Renderer();

	bool Initialize();

	void RunLoop();

	void ProcessInput();
	void Update();
	void Render();

	bool Load();

	void SetRunning(bool sel) { mKeepRunning = sel; }
	bool KeepRunning() { return mKeepRunning; }

	bool CreateShader();

	bool* GetKeys() { return mKeys; }

	class Texture* GetTexture(const std::string& filePath);
private:
	SDL_Window* mWindow;
	SDL_GLContext mContext;

	int mWidth;
	int mHeight;

	bool mKeepRunning;
	
	Uint32 mTicks;
	float mdeltaTime;

	glm::mat4 mVP;
	glm::mat4 mView;
	glm::mat4 mProj;

	std::vector<class Model*> mModels;
	std::vector<class Mesh*>  mMeshes;
	std::unordered_map<std::string, class Texture*> mTextures;

	class Shader* mShader;

	bool* mKeys;
};