#include "ShipObject.h"

namespace EngineOpenGL
{
	bool ShipObject::CheckBounds()
	{
		return false;
	}

	ShipObject::ShipObject()
	{
		this->model = new Model();
		this->model->SetModelToSquare(0.2f, 0.2f);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
	}


	ShipObject::~ShipObject()
	{
		delete this->model;

	}
	void ShipObject::Update()
	{
	}

	void ShipObject::Render(Camera cam)
	{
		this->model->LinkShader();
		this->model->Bind();
		glUseProgram(this->model->GetShaderID());
		GLint uniformLoc = glGetUniformLocation(this->model->GetShaderID(), "renderType");
		GLint worldMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "WorldMatrix");
		GLint shapeColorLoc = glGetUniformLocation(this->model->GetShaderID(), "shapeColour");
		GLint viewMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "ViewMatrix");
		GLint projectMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "ProjectionMatrix");
		glProgramUniform1i(this->model->GetShaderID(), uniformLoc, 1);
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(this->Transform.GetMatrix()));
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(cam.GetViewMatrix()));
		glUniformMatrix4fv(projectMatrixLoc, 1, GL_FALSE, glm::value_ptr(cam.GetProjectionMatrix()));
		glUniform3f(shapeColorLoc, 0.0f, 0.0f, 0.0f);
		this->model->Render();
		this->model->Unbind();
		this->model->DetachShader();
	}

	Model * ShipObject::GetModel()
	{
		return this->model;
	}
}
