#pragma once
#include <string>

class Texture
{
public:
	Texture(class Renderer* renderer);
	~Texture();

	bool Load(const std::string& filePath);
	void Unload();

	void Activate();
private:
	unsigned int mTextureID;

	int mWidth;
	int mHeight;
	int mChannels;

	class Renderer* mOwner;
};