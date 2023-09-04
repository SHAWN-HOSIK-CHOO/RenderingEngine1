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
	,mdeltaTime(0.0f)
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

	mTicks = SDL_GetTicks();

	return true;
}

void Renderer::RunLoop()
{
	while(mKeepRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Renderer::ProcessInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			mKeepRunning = false;
			break;
		default:
			break;
		}
	}
}

void Renderer::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(),mTicks + 16));

	mdeltaTime = (SDL_GetTicks() - mTicks) / 1000.0f;
	if (mdeltaTime > 0.05f)
	{
		mdeltaTime = 0.05f;
	}

	mTicks = SDL_GetTicks();

	for (auto model : mModels)
	{
		model->Update(mdeltaTime);
	}
}

void Renderer::Render()
{
	glClearColor(0.86f,0.86f,0.86f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	mShader->Activate();
	mShader->SetViewProjMatrix(mVP);
	
	auto it = mModels.begin();
	for (;it != mModels.end(); it++)
	{
		mShader->SetWorldTransMatrix((*it)->GetWorldTransMatrix());
		(*it)->Activate();
		(*it)->Draw();
	}
	

	SDL_GL_SwapWindow(mWindow);
}

bool Renderer::Load()
{
	Mesh* cubeMesh1 = new Mesh();
	if (!cubeMesh1->Load("plz"))
	{
		SDL_Log("Mesh1 Loading Failed");
		return false;
	}
	cubeMesh1->Activate();
	mMeshes.emplace_back(cubeMesh1);

	Mesh* cubeMesh2 = new Mesh();
	if (!cubeMesh2->Load("plz"))
	{
		SDL_Log("Mesh2 Loading Failed");
		return false;
	}
	cubeMesh2->Activate();
	mMeshes.emplace_back(cubeMesh2);

	Model* cubeModel1 = new Model(this);
	cubeModel1->AddMesh(cubeMesh1);
	cubeModel1->ComputeWorldTransform();
	mModels.emplace_back(cubeModel1);

	Model* cubeModel2 = new Model(this);
	cubeModel2->AddMesh(cubeMesh1);
	cubeModel2->SetPosition(glm::vec3(-3.0f,0.0f,-3.0f));
	cubeModel2->ComputeWorldTransform();
	mModels.emplace_back(cubeModel2);

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

