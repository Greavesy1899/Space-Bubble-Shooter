#ifndef LIGHT_OBJECT
#define LIGHT_OBJECT

#include <GL/glew.h>
#include <glm/glm.hpp>

class LightObject
{
	glm::vec3 position;
	glm::vec3 colour;
	GLfloat intensity;

public:
	LightObject();
	~LightObject();

	void SetPosition(glm::vec3& pos);
	void SetColour(glm::vec3& col);
	void SetIntensity(GLfloat val);
	glm::vec3 GetPosition() const;
	glm::vec3 GetColour() const;
	GLfloat GetIntensity() const;
};
#endif
