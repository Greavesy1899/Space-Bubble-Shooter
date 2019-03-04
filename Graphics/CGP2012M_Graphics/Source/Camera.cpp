#include "Camera.h"

namespace EngineOpenGL
{
	Camera::Camera()
	{
		this->projectionMatrix = glm::mat4(1.0f);
		this->viewMatrix = glm::mat4(1.0f);
		this->screenNear = 0.0f;
		this->screenFar = 5.0f;
		this->isOrtho = false;
	}

	Camera::~Camera()
	{
	}

	void Camera::SetOrthographic(float width, float height)
	{
		float ratio = width / height;
		this->projectionMatrix = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, this->screenNear, this->screenFar);
		this->isOrtho = true;
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
