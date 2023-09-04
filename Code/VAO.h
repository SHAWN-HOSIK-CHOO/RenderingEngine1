#pragma once

class VAO
{
public:
	VAO();
	~VAO();

	void Load(const float* verts, unsigned int vnum, const unsigned int* indices, unsigned int inum);

	void Activate();

	void Unload();

	unsigned int GetNumVerts() { return mNumVerts; }
	unsigned int GetNumIndices() { return mNumIndices; }

private:
	unsigned int mNumVerts;
	unsigned int mNumIndices;

	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	unsigned int mVAO;
};