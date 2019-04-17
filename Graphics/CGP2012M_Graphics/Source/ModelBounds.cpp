#include "ModelBounds.h"

namespace EngineOpenGL
{
	ModelBounds::ModelBounds()
	{
		this->minimum = glm::vec3(0);
		this->maximum = glm::vec3(0);
		this->radius = 0.0f;
		this->centre = glm::vec3(0.0f);
	}
	ModelBounds::ModelBounds(glm::vec3 min, glm::vec3 max)
	{
		//create bounding box
		this->minimum = min;
		this->maximum = max;

		this->centre = glm::vec3(
			(this->minimum.x + this->maximum.x) / 2.0f,
			(this->minimum.y + this->maximum.y) / 2.0f,
			(this->minimum.z + this->maximum.z) / 2.0f
		);

		this->radius = glm::distance(this->centre, this->maximum);

	}
	glm::vec3 ModelBounds::GetMinimum() const
	{
		return this->minimum;
	}

	glm::vec3 ModelBounds::GetMaximum() const
	{
		return this->maximum;
	}
	GLfloat ModelBounds::GetWidth() const
	{
		return this->maximum.x - this->minimum.x;
	}
	GLfloat ModelBounds::GetHeight() const
	{
		return this->maximum.y - this->maximum.y;
	}
	glm::vec3 ModelBounds::GetCentre() const
	{
		return this->centre;
	}
	GLfloat ModelBounds::GetRadius() const
	{
		return this->radius;
	}
}
