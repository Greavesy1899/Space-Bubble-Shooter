#ifndef LIGHT_OBJECT
#define LIGHT_OBJECT

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace EngineOpenGL
{
	class LightObject
	{
		struct DirectLight
		{
			glm::vec3 direction;
			glm::vec3 colour;
			GLfloat intensity;
		};

		struct PointLight
		{
			glm::vec3 position;
			glm::vec3 ambient;
			glm::vec3 diffuse;
			GLfloat constant;
			GLfloat linear;
			GLfloat quadratic;
		};

		DirectLight directLight;
		
	public:
		LightObject();
		~LightObject();

		PointLight pointLight[4];

		void SetDirectLight(DirectLight& light);
		void SetPointLight(GLint& idx, PointLight& light);
		DirectLight GetDirectLight();
		PointLight GetPointLight(GLint& idx);
	};
}
#endif
