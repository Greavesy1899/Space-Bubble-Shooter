#include "BoundingBox.h"

namespace EngineOpenGL
{
	BoundingBox::BoundingBox()
	{
		this->minimum = glm::vec3(0);
		this->maximum = glm::vec3(0);
	}
	BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max)
	{
		this->minimum = min;
		this->maximum = max;
	}
	glm::vec3 BoundingBox::GetMinimum() const
	{
		return this->minimum;
	}

	glm::vec3 BoundingBox::GetMaximum() const
	{
		return this->maximum;
	}
}
