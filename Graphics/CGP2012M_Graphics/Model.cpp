#include "Model.h"

Model::Model()
{
	this->vertices[18];
	this->vertices[0] = -0.9f;
	this->vertices[1] = -0.5f;
	this->vertices[2] = 0.0f;
	this->vertices[3] = 0.0f;
	this->vertices[4] = -0.5f;
	this->vertices[5] = 0.0f;
	this->vertices[6] = 0.45f;
	this->vertices[7] = 0.5f;
	this->vertices[8] = 0.0f;
	this->vertices[9] = 0.0f;
	this->vertices[10] = -0.5f;
	this->vertices[11] = 0.0f;
	this->vertices[12] = 0.9f;
	this->vertices[13] = -0.5f;
	this->vertices[14] = 0.0f;
	this->vertices[15] = 0.7f;
	this->vertices[16] = 0.5f;
	this->vertices[17] = 0.0f;
}


Model::~Model()
{
	glDeleteBuffers(1, &this->vBuffer);
	glDeleteVertexArrays(1, &this->vArray);
}

bool Model::Init()
{
	glGenBuffers(1, &this->vBuffer);
	glGenVertexArrays(1, &this->vArray);
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
	glBindVertexArray(this->vArray);
	glBindBuffer(GL_ARRAY_BUFFER, this->vBuffer);
	return true;
}

bool Model::Build()
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	return true;
}

bool Model::Render()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	return true;
}
