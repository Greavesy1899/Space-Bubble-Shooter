#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>

#include "TextureClass.h"
#include "SingletonManager.h"
#include "ShaderProgram.h"

namespace EngineOpenGL
{
	class Model
	{
	public:
		struct VertexLayout
		{
			glm::vec3 position;
			glm::vec3 color;
			glm::vec2 uv;

			VertexLayout();
			VertexLayout(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat u, GLfloat v);
		};

	private:
		VertexLayout* vertices;
		GLushort* indices;
		TextureClass* texture;
		ShaderProgram* shader;
		GLuint numVertices;
		GLuint numTriangles;
		GLuint vbo;
		GLuint ibo;
		GLuint vao;

	public:
		Model();
		~Model();

		bool Init();
		bool SetVertices(VertexLayout* vl, GLuint numVertices);
		bool SetIndices(GLushort* inds, GLuint numTringles);
		bool SetModelToSquare(GLfloat widthFactor, GLfloat heightFactor);
		bool SetModelToCircle(GLfloat radiusFactor);
		int GetShaderID() const;
		bool Unbind();
		bool Bind();
		bool Build();
		bool Render();
	};
}
#endif

