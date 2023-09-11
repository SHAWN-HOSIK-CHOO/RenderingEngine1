#include "VAO.h"
#include <GL/glew.h>


VAO::VAO()
	:mNumIndices(0)
	,mNumVerts(0)
	,mIndexBuffer(0)
	,mVertexBuffer(0)
	,mVAO(0)
{
}

VAO::~VAO()
{
	glDeleteBuffers(1,&mVertexBuffer);
	glDeleteBuffers(1,&mIndexBuffer);
	glDeleteVertexArrays(1,&mVAO);
}

void VAO::Load(const float* verts, unsigned int vnum, const unsigned int* indices, unsigned int inum)
{
	mNumVerts = vnum;
	mNumIndices = inum;

	//

	glGenVertexArrays(1,&mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1,&mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vnum * 8 * sizeof(float),verts,GL_STATIC_DRAW);

	glGenBuffers(1,&mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,inum * sizeof(unsigned int),indices,GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*8,0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*8,reinterpret_cast<void*>(sizeof(float) * 3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(float) * 8,reinterpret_cast<void*>(sizeof(float) * 6));
}

void VAO::Activate()
{
	glBindVertexArray(mVAO);
}

void VAO::Unload()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVAO);
}

