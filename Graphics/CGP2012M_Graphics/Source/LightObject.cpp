#include "LightObject.h"

LightObject::LightObject()
{
	this->position = glm::vec3(0.0f);
	this->intensity = 0.0f;
}

LightObject::~LightObject()
{
}

void LightObject::SetPosition(glm::vec3& pos)
{
	this->position = pos;
}

void LightObject::SetColour(glm::vec3& col)
{
	this->colour = col;
}

void LightObject::SetIntensity(GLfloat val)
{
	this->intensity = val;
}

glm::vec3 LightObject::GetPosition() const
{
	return this->position;
}

glm::vec3 LightObject::GetColour() const
{
	return this->colour;
}

GLfloat LightObject::GetIntensity() const
{
	return this->intensity;
}
