#include "LightObject.h"

namespace EngineOpenGL
{
	LightObject::LightObject()
	{
		this->directLight = DirectLight();
		this->directLight.direction = glm::vec3(-0.5f, -0.1f, -1.0f);
		this->directLight.colour = glm::vec3(0.33f, 0.33f, 0.33f);
		this->directLight.intensity = 0.5f;

		PointLight templatel = PointLight();
		templatel.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
		templatel.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		templatel.constant = 1.0f;
		templatel.linear = 0.22f;
		templatel.quadratic = 0.20f;
		templatel.position = glm::vec3(99.0f);

		this->pointLight[0] = templatel;
		this->pointLight[1] = templatel;
		this->pointLight[2] = templatel;
		this->pointLight[3] = templatel;
	}

	LightObject::~LightObject()
	{
	}

	void LightObject::SetDirectLight(DirectLight& light)
	{
		this->directLight = light;
	}

	void LightObject::SetPointLight(GLint& idx, PointLight& light)
	{
		this->pointLight[idx] = light;
	}

	LightObject::DirectLight LightObject::GetDirectLight()
	{
		return this->directLight;
	}

	LightObject::PointLight LightObject::GetPointLight(GLint& idx)
	{
		return this->pointLight[idx];
	}
}