#include "BubbleObject.h"

namespace EngineOpenGL
{
	bool BubbleObject::CheckBounds()
	{
		BoundingBox bbox = this->model->GetBBox();
		glm::vec3 pos = this->Transform.GetPosition();

		float xValue = 0.0f;
		float yValue = 0.0f;

		if (pos.x + bbox.GetMinimum().x < -1.0) {
			this->direction += 90;
			std::cout << this->direction << std::endl;
		}

		if (pos.y + bbox.GetMinimum().y < -1.0f) {
			this->direction = -this->direction;
			std::cout << this->direction << std::endl;
		}

		if (pos.x + bbox.GetMaximum().x > 1.0f) {
			this->direction = -this->direction;
			std::cout << this->direction << std::endl;
		}

		if (pos.y + bbox.GetMaximum().y > 1.0f) {
			this->direction -= 90;
			std::cout << this->direction << std::endl;
		}

		this->Transform.Translate(glm::vec3((float)cos(direction)*0.01f, (float)sin(direction)*0.01f, 0.0f));
		return true;
	}
	BubbleObject::BubbleObject()
	{
		this->model = new Model();
		this->model->SetModelToCircle(0.25f);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->direction = rand() % 360;
	}

	BubbleObject::~BubbleObject()
	{
		delete this->model;
	}

	void BubbleObject::Update()
	{
		CheckBounds();
		//if(CheckBounds())
		//	this->Transform.Translate(glm::vec3((float)cos(direction)*0.01f, (float)sin(direction)*0.01f, 0.0f));
		//else
		//	this->direction = rand() % 360;
	}

	void BubbleObject::Render()
	{
		this->model->LinkShader();
		this->model->Bind();
		this->model->Bind();
		glUseProgram(this->model->GetShaderID());
		GLint uniformLoc = glGetUniformLocation(this->model->GetShaderID(), "enableTex");
		GLint worldMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "WorldMatrix");
		glProgramUniform1i(this->model->GetShaderID(), uniformLoc, 0);
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(this->Transform.GetMatrix()));
		this->model->Render();
		this->model->Unbind();
		this->model->DetachShader();
	}

	Model* BubbleObject::GetModel()
	{
		return this->model;
	}
}