#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <GL/glew.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace EngineOpenGL
{
	class ShaderProgram
	{
	private:
		GLuint shaderProgramID;
		GLuint vertexShader;
		GLuint fragmentShader;

	public:
		ShaderProgram();
		~ShaderProgram();

		bool Init();
		bool Attach();
		bool Detach();
		bool Link();

		bool ReadShaderFromPath(const char* fileName, short type);

		void SetUniformInt(std::string uniformName, GLint val);
		void SetUniformFloat(std::string uniformName, GLfloat val);
		void SetUniformFloat(std::string uniformName, GLfloat val1, GLfloat val2, GLfloat val3);
		void SetUniformMatrix(std::string uniformName, glm::mat4 val);

		GLuint GetProgramID();


	};
}
#endif
