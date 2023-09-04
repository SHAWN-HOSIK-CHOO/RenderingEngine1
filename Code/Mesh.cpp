#include "Mesh.h"
#include "VAO.h"
#include <GL/glew.h>

Mesh::Mesh()
	: mVertexArray(nullptr)
{

}

Mesh::~Mesh()
{
	Unload();
}

bool Mesh::Load(const std::string& filePath)
{
	mVertexArray = new VAO();

	//---------------------------------------------------------------
	// Loading Procedure Required
	// Temporary data

	float vertPos[] = {
			-0.5f, -0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f
	};

	unsigned int indPos[] = {
			0, 1, 2,
			2, 1, 3,
			2, 3, 4,
			4, 3, 5,
			4, 5, 6,
			6, 5, 7,
			6, 7, 0,
			0, 7, 1,
			6, 0, 2,
			2, 4, 6,
			7, 5, 3,
			7, 3, 1
	};


	//Temp
	//----------------------------------------------------------------
	unsigned int numvert = sizeof(vertPos) / sizeof(float);
	unsigned int numindice = sizeof(indPos) / sizeof(unsigned int);

	CreateVAO(vertPos, numvert, indPos, numindice);

	return true;
}

void Mesh::Unload()
{
	mVertexArray->Unload();
}

void Mesh::Activate()
{
	mVertexArray->Activate();
}


void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::CreateVAO(const float* v, unsigned int nv, const unsigned int* i, unsigned int ni)
{
	mVertexArray->Load(v, nv, i, ni);
}

