#include "Renderer.h"
#include "VAO.h"
#include "Shader.h"
#include "Model.h"
#include "Mesh.h"

Renderer::Renderer(int width, int height)
	:mWidth(width)
	, mHeight(height)
	,mKeepRunning(true)
	,mShader(nullptr)
{
}

Renderer::~Renderer()
{
	SDL_GL_DeleteContext(mContext);
}

bool Renderer::Initialize()
{
	mWindow = SDL_CreateWindow("Renderer One",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,mWidth,mHeight,SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);

	mContext = SDL_GL_CreateContext(mWindow);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		SDL_Log("GLEW Init Failed");
		return false;
	}

	if (!CreateShader())
	{
		SDL_Log("Failed To Load Shader");
		return false;
	}

	if (!Load())
	{
		return false;
	}

	return true;
}

void Renderer::Render()
{
	glClearColor(0.86f,0.86f,0.86f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	;

	mShader->Activate();
	mShader->SetViewProjMatrix(mVP);
	mShader->SetWorldTransMatrix(glm::mat4(1.0f));

	mModels.at(0)->Activate();
	mModels.at(0)->Draw();
	

	SDL_GL_SwapWindow(mWindow);
}

bool Renderer::Load()
{
	Mesh* cubeMesh = new Mesh();
	if (!cubeMesh->Load("plz"))
	{
		SDL_Log("Mesh Loading Failed");
		return false;
	}
	cubeMesh->Activate();
	mMeshes.emplace_back(cubeMesh);

	Model* cubeModel = new Model(this);
	cubeModel->AddMesh(cubeMesh);
	mModels.emplace_back(cubeModel);

	return true;
}

bool Renderer::CreateShader()
{
	mShader = new Shader();
	if (!mShader->Load("Code/BasicVert.vert","Code/BasicFrag.frag"))
	{
		SDL_Log("Shader Load Failed");
		return false;
	}

	mView = glm::lookAt(glm::vec3(2, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	mProj = glm::perspective(glm::radians(70.0f), static_cast<float>(mWidth) / static_cast<float>(mHeight), 0.05f, 1000.0f);
	mVP = mProj * mView;

	mShader->SetViewProjMatrix(mVP);
	return true;
}

