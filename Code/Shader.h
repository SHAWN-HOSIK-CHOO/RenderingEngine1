#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
	Shader();
	~Shader();

	bool Load(const std::string& vs,const std::string& fs);

	void Unload();

	void Activate();

	void SetMatrixUniform(const char* name, const glm::mat4& mat);

	void SetViewProjMatrix(const glm::mat4& mat);
	void SetWorldTransMatrix(const glm::mat4& mat);
private:
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram(GLuint program);

	GLuint mVertShader;
	GLuint mFragShader;
	GLuint mProgram;
};