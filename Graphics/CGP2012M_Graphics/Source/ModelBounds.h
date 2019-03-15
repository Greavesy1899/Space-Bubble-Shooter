#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace EngineOpenGL
{
	class ModelBounds
	{
		glm::vec3 minimum;
		glm::vec3 maximum;
		glm::vec3 centre;
		GLfloat radius;

	public:
		ModelBounds();
		ModelBounds(glm::vec3 min, glm::vec3 max);
		glm::vec3 GetMinimum() const;
		glm::vec3 GetMaximum() const;
		GLfloat GetWidth() const;
		GLfloat GetHeight() const;
		glm::vec3 GetCentre() const;
		GLfloat GetRadius() const;

	};
}
#endif