#include "BulletObject.h"

namespace EngineOpenGL
{

	BulletObject::BulletObject()
	{
		OBJLoader loader = OBJLoader();
		loader.ParseOBJ("Models/bullet.obj");
		this->model = new Model();
		this->model->SetModelToObj(loader);
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
		glm::vec3 pos = euler * 0.1f * TransformMatrix::GetStaticUp();
		this->Transform.Translate(glm::vec3((float)sin(pos.x)*0.1f, (float)cos(pos.x)*0.1f, 0.0f));
	}
}
