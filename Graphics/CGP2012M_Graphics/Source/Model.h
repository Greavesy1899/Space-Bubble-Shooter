#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>

class Model
{
public:
	struct VertexLayout
	{
		glm::vec3 position;
		glm::vec3 color;

		VertexLayout()
		{
			this->position = glm::vec3();
			this->color = glm::vec3();
		}
		VertexLayout(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b)
		{
			this->position = glm::vec3(x, y, z);
			this->color = glm::vec3(r, g, b);
		}
	};

private:
	VertexLayout* vertices;
	GLuint numVertices;
	GLuint numTriangles;
	GLushort* indices;
	GLuint vbo;
	GLuint ibo;
	GLuint vao;

public:
	Model();
	~Model();

	bool Init();
	bool SetVertices(VertexLayout* vl, GLuint numVertices);
	bool SetIndices(GLushort* inds, GLuint numTringles);
	bool Unbind();
	bool Bind();
	bool Build();
	bool Render();
};

#endif

