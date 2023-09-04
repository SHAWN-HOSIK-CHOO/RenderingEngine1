#pragma once
#include <string>


class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& filePath);
	void Unload();
	
	class VAO* GetVAO() { return mVertexArray; }

	void Activate();

	void Draw();
private:
	void CreateVAO(const float* v, unsigned int nv, const unsigned int* i, unsigned int ni);
	
	class VAO* mVertexArray;
};