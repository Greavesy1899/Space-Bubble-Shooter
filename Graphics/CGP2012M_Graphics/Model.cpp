#include "Model.h"

Model::Model()
{
	GLushort inds[6];
	inds[0] = 0;
	inds[1] = 1;
	inds[2] = 2;
	inds[3] = 3;
	inds[4] = 4;
	inds[5] = 5;
	this->numTriangles = 2;
}


Model::~Model()
{
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ibo);
	glDeleteVertexArrays(1, &this->vao);
	delete[] this->indices;
	delete[] this->vertices;
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
	glBufferData(GL_ARRAY_BUFFER, this->numVertices*sizeof(VertexLayout), this->vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24, this->indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);
	return true;
}

bool Model::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, 0);
	return true;
}