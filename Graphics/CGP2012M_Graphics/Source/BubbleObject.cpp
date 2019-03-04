#include "BubbleObject.h"

namespace EngineOpenGL
{
	bool BubbleObject::CheckBounds()
	{
		BoundingBox bbox = this->model->GetBBox();
		glm::vec3 pos = this->Transform.GetPosition();

		if (pos.x + bbox.GetMinimum().x < -4.0f) {
			this->xDirection = -this->xDirection;
			this->shapeColour.g = 0.0f;
			this->shapeColour.r = 0.0f;
			this->shapeColour.b = 1.0f;
		}

		if (pos.y + bbox.GetMinimum().y < -4.0f) {
			this->yDirection = -this->yDirection;
			this->shapeColour.g = 1.0f;
			this->shapeColour.r = 0.0f;
			this->shapeColour.b = 1.0f;
		}

		if (pos.x + bbox.GetMaximum().x > 4.0f) {
			this->xDirection = -this->xDirection;
			this->shapeColour.g = 1.0f;
			this->shapeColour.r = 1.0f;
			this->shapeColour.b = 0.0f;
		}

		if (pos.y + bbox.GetMaximum().y > 4.0f) {
			this->yDirection = -this->yDirection;
			this->shapeColour.g = 1.0f;
			this->shapeColour.r = 1.0f;
			this->shapeColour.b = 1.0f;
		}

		this->Transform.Translate(glm::vec3(sin(this->xDirection)*0.01f, sin(this->yDirection)*0.01f, 0.0f));
		return true;
	}
	BubbleObject::BubbleObject()
	{
		this->model = new Model();
		this->model->SetModelToCircle(0.125f);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->xDirection = rand() % 360;
		this->yDirection = rand() % 360;
		this->shapeColour = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	BubbleObject::~BubbleObject()
	{
		delete this->model;
	}

	void BubbleObject::Update()
	{
		CheckBounds();
		this->Transform.Translate(glm::vec3((float)sin(xDirection)*0.01f, (float)sin(yDirection)*0.01f, 0.0f));
	}

	void BubbleObject::Render(Camera cam)
	{
		this->model->LinkShader();
		this->model->Bind();
		glUseProgram(this->model->GetShaderID());
		GLint uniformLoc = glGetUniformLocation(this->model->GetShaderID(), "renderType");
		GLint worldMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "WorldMatrix");
		GLint shapeColorLoc = glGetUniformLocation(this->model->GetShaderID(), "shapeColour");
		GLint viewMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "ViewMatrix");
		GLint projectMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "ProjectionMatrix");
		glProgramUniform1i(this->model->GetShaderID(), uniformLoc, 2);
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(this->Transform.GetMatrix()));
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(cam.GetViewMatrix()));
		glUniformMatrix4fv(projectMatrixLoc, 1, GL_FALSE, glm::value_ptr(cam.GetProjectionMatrix()));
		glUniform3f(shapeColorLoc, this->shapeColour.r, this->shapeColour.g, this->shapeColour.b);
		this->model->Render();
		this->model->Unbind();
		this->model->DetachShader();
	}

	Model* BubbleObject::GetModel()
	{
		return this->model;
	}
}