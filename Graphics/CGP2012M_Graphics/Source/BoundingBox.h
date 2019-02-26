#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include <GL/glew.h>
#include <glm/glm.hpp>
//#include "Model.h"

namespace EngineOpenGL
{
	class BoundingBox
	{

		glm::vec3 minimum;
		glm::vec3 maximum;

	public:
		BoundingBox();
		BoundingBox(glm::vec3 min, glm::vec3 max);
		glm::vec3 GetMinimum() const;
		glm::vec3 GetMaximum() const;

	};
}
#endif