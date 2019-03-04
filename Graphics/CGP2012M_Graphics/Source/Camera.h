#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace EngineOpenGL
{
	class Camera
	{
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		bool isOrtho;
		float screenNear;
		float screenFar;

	public:
		Camera();
		~Camera();

		void SetOrthographic(float width, float height);
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();
	};
}
#endif

