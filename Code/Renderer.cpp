#include "Renderer.h"
#include "VAO.h"

Renderer::Renderer(int width, int height)
	:mWidth(width)
	, mHeight(height)
	,mKeepRunning(true)
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

	mVertexArray = new VAO;

	return true;
}

void Renderer::Render()
{

}

void Renderer::CreateVAO(const float* v, unsigned int nv, const unsigned int* i, unsigned int ni)
{
	mVertexArray->Load(v,nv,i,ni);
}