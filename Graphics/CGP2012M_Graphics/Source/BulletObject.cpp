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

	void EngineOpenGL::BulletObject::Render(Camera cam)
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
		glUniform3f(shapeColorLoc, 1.0f, 0.0f, 0.0f);
		this->model->Render();
		this->model->Unbind();
		this->model->DetachShader();
	}

	Model * EngineOpenGL::BulletObject::GetModel()
	{
		return this->model;
	}
}
