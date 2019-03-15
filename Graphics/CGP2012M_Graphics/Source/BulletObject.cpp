#include "BulletObject.h"

namespace EngineOpenGL
{

	BulletObject::BulletObject()
	{
		this->model = new Model();
		this->model->SetModelToSquare(0.05f, 0.1f);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->SetRenderType(RenderTypes::COLOUR);
		this->SetDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	BulletObject::~BulletObject()
	{
		delete this->model;
	}

	void EngineOpenGL::BulletObject::Update()
	{
		auto euler = this->Transform.GetEuler();
		glm::vec3 pos = euler * 0.1f * TransformMatrix::GetUp();
		this->Transform.Translate(glm::vec3((float)sin(pos.x)*0.1f, (float)cos(pos.x)*0.1f, 0.0f));
	}
}
