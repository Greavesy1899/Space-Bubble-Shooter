#include "Source\BubbleObject.h"

EngineOpenGL::BubbleObject::BubbleObject()
{
	this->model = new Model();
	this->model->SetModelToCircle(0.25f);
	this->model->Init();
	this->model->Bind();
	this->model->Build();
	this->model->Unbind();
	this->model->Transform.SetPosition(glm::vec3(-0.5f, 0.5f, 0.0f));
}

EngineOpenGL::BubbleObject::~BubbleObject()
{
	delete this->model;
}

void EngineOpenGL::BubbleObject::Update()
{
	this->model->Transform.Translate(glm::vec3(0.0f, -0.01f, 0.0f));
}

void EngineOpenGL::BubbleObject::Render()
{
	this->model->LinkShader();
	this->model->Bind();
	this->model->Bind();
	glUseProgram(this->model->GetShaderID());
	GLint uniformLoc = glGetUniformLocation(this->model->GetShaderID(), "enableTex");
	GLint worldMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "WorldMatrix");
	glProgramUniform1i(this->model->GetShaderID(), uniformLoc, 0);
	glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(this->model->Transform.GetMatrix()));
	this->model->Render();
	this->model->Unbind();
	this->model->DetachShader();
}
