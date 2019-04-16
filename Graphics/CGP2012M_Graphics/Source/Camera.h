#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TransformMatrix.h"

namespace EngineOpenGL
{
	class Camera
	{
		glm::mat4 projectionMatrix;
		float screenNear;
		float screenFar;
		float aspect;

	public:
		Camera(float w, float h);
		Camera();
		~Camera();

		void SetOrthographic(float width, float height);
		void SetPerspective(float width, float height);
		TransformMatrix ViewMatrix;
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();
	};
}
#endif

