#include "Camera.h"
#include "GL/glew.h"

namespace EngineOpenGL
{
	Camera::Camera(float w, float h)
	{
		this->projectionMatrix = glm::mat4(1.0f);
		this->viewMatrix = glm::mat4(1.0f);
		this->screenNear = 0.0f;
		this->screenFar = 5.0f;
		this->isOrtho = false;
		this->aspect = w / h;
	}

	Camera::~Camera()
	{
	}

	void Camera::SetOrthographic(float width, float height)
	{
		this->projectionMatrix = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, this->screenNear, this->screenFar);
		this->isOrtho = true;
		float updatedWidth = height * aspect;
		glViewport((width-updatedWidth)/2, 0, updatedWidth, height);
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return this->projectionMatrix;
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return this->viewMatrix;
	}


}
