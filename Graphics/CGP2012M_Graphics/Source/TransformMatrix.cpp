#include "TransformMatrix.h"
#include <iostream>

TransformMatrix::TransformMatrix()
{
	this->matrix = glm::mat4(1.0f);
}


TransformMatrix::~TransformMatrix()
{
}

glm::vec3 TransformMatrix::GetPosition() const
{
	glm::vec3 pos = glm::vec3(0);
	pos.x = this->matrix[3][0];
	pos.y = this->matrix[3][1];
	pos.z = this->matrix[3][2];
	return pos;
}

glm::vec3 TransformMatrix::GetScale() const
{
	glm::vec3 scale = glm::vec3(0);
	scale.x = this->matrix[0][0];
	scale.y = this->matrix[1][1];
	scale.z = this->matrix[2][2];
	return scale;
}

glm::vec3 TransformMatrix::GetEuler() const
{
	//x = roll;
	//y = pitch;
	//z = yaw;

	glm::vec3 rotation = glm::vec3(0);
	rotation.y = -asin(this->matrix[2][0]);

	//Gymbal lock: pitch = -90
	if (this->matrix[2][0] == 1) {
		rotation.x = 0.0f;
		rotation.z = atan2(-this->matrix[0][1], -this->matrix[0][2]);
	}

	//Gymbal lock: pitch = 90
	else if (this->matrix[2][0] == -1) {
		rotation.x = 0.0f;
		rotation.z = atan2(this->matrix[0][1], this->matrix[0][2]);
	}
	//General solution
	else {
		rotation.x = atan2(this->matrix[1][0], this->matrix[0][0]);
		rotation.z = atan2(this->matrix[2][1], this->matrix[2][2]);
	}
	return rotation;
}

glm::mat4 TransformMatrix::GetMatrix() const
{
	return this->matrix;
}

void TransformMatrix::Translate(glm::vec3 pos)
{
	this->matrix = glm::translate(this->matrix, pos);
}

void TransformMatrix::Rotate(glm::vec3 rotate, float angle)
{
	this->matrix = glm::rotate(this->matrix, angle, rotate);
}

void TransformMatrix::Scale(glm::vec3 scale)
{
	this->matrix = glm::scale(this->matrix, scale);
}

void TransformMatrix::SetPosition(glm::vec3 pos)
{
	this->matrix = glm::mat4(1.0f);
	this->matrix = glm::translate(this->matrix, pos);
}

void TransformMatrix::SetScale(glm::vec3 scale)
{
	this->matrix = glm::mat4(1.0f);
	this->matrix = glm::scale(this->matrix, scale);
}

void TransformMatrix::SetRotation(glm::vec3 rot, float angle)
{
	this->matrix = glm::mat4(1.0f);
	this->matrix = glm::rotate(this->matrix, angle, rot);
}
