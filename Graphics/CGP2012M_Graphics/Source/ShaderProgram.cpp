#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace EngineOpenGL
{
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
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		return true;
	}

	bool ShaderProgram::Attach()
	{
		glAttachShader(this->shaderProgramID, vertexShader);
		glAttachShader(this->shaderProgramID, fragmentShader);
		return true;
	}

	bool ShaderProgram::Detach()
	{
		glDetachShader(this->shaderProgramID, vertexShader);
		glDetachShader(this->shaderProgramID, fragmentShader);
		return true;
	}

	bool ShaderProgram::Link()
	{
		glLinkProgram(this->shaderProgramID);
		return true;
	}

	bool ShaderProgram::ReadShaderFromPath(const char* fileName, short type)
	{
		if (!std::experimental::filesystem::exists(fileName))
		{
			std::cout << "Failed to locate file: " << fileName << std::endl;
			return false;
		}

		std::ifstream inFile(fileName);
		std::string text = "";
		int shaderBuff = -1;
		const char* ptr = nullptr;
		while (inFile.good())
		{
			std::string line;
			std::getline(inFile, line);
			text.append(line + "\n");
		}
		switch (type)
		{
		case 0:
			ptr = text.c_str();
			shaderBuff = this->vertexShader;
			break;
		case 1:
			ptr = text.c_str();
			shaderBuff = this->fragmentShader;
			break;
		default:
			printf("Unknown type!");
			break;
		}
		//std::cout << "import success:" << std::endl;
		//std::cout << text.c_str() << std::endl;

		glShaderSource(shaderBuff, 1, &ptr, NULL);
		glCompileShader(shaderBuff);

		GLint success;
		GLchar infoLog[512];

		glGetShaderiv(shaderBuff, GL_COMPILE_STATUS, &success);
		//std::cout << "Shader compile: " << shaderBuff << " " << success << std::endl;

		if (!success)
		{
			glGetShaderInfoLog(shaderBuff, 512, NULL, infoLog);
			std::cout << "Failed to compile shader:\n" << infoLog << std::endl;
		}

		return true;
	}

	void ShaderProgram::SetUniformInt(std::string uniformName, GLint val)
	{
		int loc = glGetUniformLocation(this->shaderProgramID, uniformName.c_str());
		glUniform1i(loc, val);
	}

	void ShaderProgram::SetUniformFloat(std::string uniformName, GLfloat val)
	{
		int loc = glGetUniformLocation(this->shaderProgramID, uniformName.c_str());
		glUniform1f(loc, val);
	}

	void ShaderProgram::SetUniformFloat(std::string uniformName, GLfloat val1, GLfloat val2, GLfloat val3)
	{
		int loc = glGetUniformLocation(this->shaderProgramID, uniformName.c_str());
		glUniform3f(loc, val1, val2, val3);
	}

	void ShaderProgram::SetUniformMatrix(std::string uniformName, glm::mat4 val)
	{
		int loc = glGetUniformLocation(this->shaderProgramID, uniformName.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
	}

	GLuint ShaderProgram::GetProgramID()
	{
		return this->shaderProgramID;
	}
}