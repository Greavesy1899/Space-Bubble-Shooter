#include "Camera.h"
#include "GL/glew.h"

namespace EngineOpenGL
{
	Camera::Camera()
	{
		this->projectionMatrix = glm::mat4(1.0f);
		this->ViewMatrix = TransformMatrix();
		this->screenNear = 0.1f;
		this->screenFar = 50.0f;
		this->aspect = 0.0f;
	}

	Camera::Camera(float w, float h)
	{
		this->projectionMatrix = glm::mat4(1.0f);
		this->ViewMatrix = TransformMatrix();
		this->ViewMatrix.SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));
		this->screenNear = 0.1f;
		this->screenFar = 50.0f;
		this->aspect = w / h;
	}

	Camera::~Camera()
	{
	}

	void Camera::SetOrthographic(float width, float height)
	{
		this->projectionMatrix = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, this->screenNear, this->screenFar);
		float updatedWidth = height * aspect;
		glViewport((width-updatedWidth)/2, 0, updatedWidth, height);
	}

	void Camera::SetPerspective(float width, float height)
	{
		this->projectionMatrix = glm::perspective(glm::radians(45.0f), this->aspect, this->screenNear, this->screenFar);
		float updatedWidth = height * aspect;
		glViewport((width - updatedWidth) / 2, 0, updatedWidth, height);

	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return this->projectionMatrix;
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return this->ViewMatrix.GetMatrix();
	}


}
