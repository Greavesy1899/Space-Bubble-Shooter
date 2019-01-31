#include "ShaderProgram.h"
#include <iostream>
#include <fstream>

ShaderProgram::ShaderProgram()
{
	this->shaderProgramID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragmentShader);
}

bool ShaderProgram::Init()
{
	//TODO : Implement error handling.
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	if (this->tempVertexPath.empty() || this->tempFragPath.empty())
		return false;

	const GLchar* temp1 = this->tempVertexPath.c_str();
	const GLchar* temp2 = this->tempFragPath.c_str();

	glShaderSource(this->vertexShader, 1,  &temp1, NULL);
	glShaderSource(this->fragmentShader, 1, &temp2, NULL);
	

	return true;
}

bool ShaderProgram::Compile()
{
	glCompileShader(this->vertexShader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
	std::cout << "Shader compile: " << this->vertexShader << " " << success << std::endl;

	if (!success)
	{
		glGetShaderInfoLog(this->vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glCompileShader(this->fragmentShader);

	glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
	std::cout << "Shader compile: " << this->fragmentShader << " " << success << std::endl;

	if (!success)
	{
		glGetShaderInfoLog(this->fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return true;
}

bool ShaderProgram::Attach()
{
	glAttachShader(this->shaderProgramID, vertexShader);
	glAttachShader(this->shaderProgramID, fragmentShader);
	return true;
}

bool ShaderProgram::Link()
{
	glLinkProgram(this->shaderProgramID);
	return true;
}

bool ShaderProgram::ReadShaderFromPath(const char* fileName, short type)
{
	std::ifstream inFile(fileName);
	std::string text = "";
	while (inFile.good())
	{
		std::string line;
		std::getline(inFile, line);
		text.append(line + "\n");
	}
	switch (type)
	{
	case 0:
		this->tempVertexPath = text;
		break;
	case 1:
		this->tempFragPath = text;
		break;
	default:
		printf("Unknown type!");
		break;
	}
	std::cout << "import success:" << std::endl;
	std::cout << text.c_str() << std::endl;

	return false;
}

GLuint ShaderProgram::GetProgramID()
{
	return this->shaderProgramID;
}
