#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <GL/glew.h>
#include <cstdio>
#include <cstdlib>
#include <string>

class ShaderProgram
{
private:
	GLuint shaderProgramID;
	GLuint vertexShader;
	GLuint fragmentShader;

	std::string tempVertexPath;
	std::string tempFragPath;


public:
	ShaderProgram();
	~ShaderProgram();

	bool Init();
	bool Compile();
	bool Attach();
	bool Link();

	bool ReadShaderFromPath(const char* fileName, short type);

	GLuint GetProgramID();
};
#endif
