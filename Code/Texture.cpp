#include "Texture.h"
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Model.h"
#include "Renderer.h"
#include <SDL2/SDL_log.h>

Texture::Texture(Renderer* renderer)
	:mTextureID(0)
	,mWidth(0)
	,mHeight(0)
	,mChannels(0)
	,mOwner(renderer)
{

}

Texture::~Texture()
{
	Unload();
}

bool Texture::Load(const std::string& filePath)
{
	unsigned char* data = stbi_load(filePath.c_str(),&mWidth,&mHeight,&mChannels,0);
	
	if (!data)
	{
		SDL_Log("Loading Texture %s Failed",filePath.c_str());
		return false;
	}

	int format = GL_RGB;

	if (mChannels == 4)
	{
		format = GL_RGBA;
	}

	glGenTextures(1,&mTextureID);
	glBindTexture(GL_TEXTURE_2D,mTextureID);
	glTexImage2D(GL_TEXTURE_2D,0,format,mWidth,mHeight,0,format,GL_UNSIGNED_BYTE,data);
	
	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1,&mTextureID);
}

void Texture::Activate()
{
	glBindTexture(GL_TEXTURE_2D,mTextureID);
}