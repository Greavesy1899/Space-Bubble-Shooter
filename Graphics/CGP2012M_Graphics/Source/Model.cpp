#include "Model.h"

namespace EngineOpenGL
{
	Model::Model()
	{

	}

	Model::~Model()
	{
		glDeleteBuffers(1, &this->vbo);
		glDeleteBuffers(1, &this->ibo);
		glDeleteVertexArrays(1, &this->vao);
		delete[] this->indices;
		delete[] this->vertices;
		delete this->texture;
	}

	bool Model::SetVertices(VertexLayout* vl, GLuint numVertices)
	{
		this->vertices = vl;
		this->numVertices = numVertices;
		return true;
	}

	bool Model::SetIndices(GLushort* inds, GLuint numTriangles)
	{
		this->indices = inds;
		this->numTriangles = numTriangles;
		return true;
	}

	//bool Model::SetByPrimitive(PrimitiveEngine::Primitive primitive)
	//{
	//	this->indices = primitive.indices;
	//	this->vertices = primitive.vertices;
	//	this->numTriangles = primitive.numIndices;
	//	this->numVertices = primitive.numVertices;
	//	return true;
	//}

	bool Model::Init()
	{
		glGenBuffers(1, &this->vbo);
		glGenBuffers(1, &this->ibo);
		glGenVertexArrays(1, &this->vao);
		return true;
	}

	bool Model::Unbind()
	{
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		return true;
	}

	bool Model::Bind()
	{
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		return true;
	}

	bool Model::Build()
	{
		glBufferData(GL_ARRAY_BUFFER, this->numVertices * sizeof(VertexLayout), this->vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numTriangles * 6, this->indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)(2 * sizeof(glm::vec3)));
		glEnableVertexAttribArray(2);
		return true;
	}

	bool Model::Render()
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, this->numTriangles * 3, GL_UNSIGNED_SHORT, 0);
		return true;
	}

	Model::VertexLayout::VertexLayout()
	{
		this->position = glm::vec3();
		this->color = glm::vec3();
		this->uv = glm::vec2();
	}

	Model::VertexLayout::VertexLayout(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat u, GLfloat v)
	{
		this->position = glm::vec3(x, y, z);
		this->color = glm::vec3(r, g, b);
		this->uv = glm::vec2(u, v);
	}
}