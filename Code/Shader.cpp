#include "Shader.h"
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>

Shader::Shader()
	:mVertShader(0)
	, mFragShader(0)
	, mProgram(0)
{

}

Shader::~Shader()
{
	glDeleteShader(mVertShader);
	glDeleteShader(mFragShader);
	glDeleteProgram(mProgram);
}

bool Shader::Load(const std::string& vs, const std::string& fs)
{
	if (!CompileShader(vs,GL_VERTEX_SHADER,mVertShader) || !CompileShader(fs,GL_FRAGMENT_SHADER,mFragShader))
	{
		SDL_Log("Shader Compile Failed");
		return false;
	}

	mProgram = glCreateProgram();
	glAttachShader(mProgram,mVertShader);
	glAttachShader(mProgram,mFragShader);
	glLinkProgram(mProgram);

	if (!IsValidProgram(mProgram))
	{
		SDL_Log("Invalid Program");
		return false;
	}
	return true;
}

void Shader::Unload()
{
	glDeleteShader(mVertShader);
	glDeleteShader(mFragShader);
	glDeleteProgram(mProgram);
}

void Shader::Activate()
{
	glUseProgram(mProgram);
}

void Shader::SetMatrixUniform(const char* name,const glm::mat4& mat)
{
	GLuint loc = glGetUniformLocation(mProgram,name);
	glUniformMatrix4fv(loc,1,GL_FALSE,&mat[0][0]);
}

void Shader::SetViewProjMatrix(const glm::mat4& mat)
{
	SetMatrixUniform("uViewProj", mat);
}

void Shader::SetWorldTransMatrix(const glm::mat4& mat)
{
	SetMatrixUniform("uWorldTrans",mat);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	std::ifstream file(fileName);
	if (file.is_open())
	{
		std::stringstream sstream;
		sstream << file.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		outShader = glCreateShader(shaderType);
		glShaderSource(outShader,1,&(contentsChar),nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Shader %s Compile Failed",fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Failed to Open File : %s",fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;

	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer,0,512);
		glGetShaderInfoLog(shader,511,nullptr,buffer);
		SDL_Log("GLSL Compile Failed : %s",buffer);

		GLint log_length;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&log_length);
		memset(buffer, 0, log_length);
		glGetShaderInfoLog(shader,log_length,NULL,buffer);
		SDL_Log("%s",buffer);

		return false;
	}

	return true;
}

bool Shader::IsValidProgram(GLuint program)
{
	GLint status;

	glGetProgramiv(program,GL_LINK_STATUS,&status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer,0,512);
		glGetProgramInfoLog(program,511,nullptr,buffer);
		SDL_Log("Program Link Failed : %s",buffer);
		return false;
	}
	return true;
}