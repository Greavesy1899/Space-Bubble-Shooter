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
		this->bulletObject = nullptr;
	}

	ShipObject::~ShipObject()
	{
		delete this->model;
	}

	void ShipObject::Input()
	{
		glm::vec3 euler = this->Transform.GetEuler();
		if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_A))
		{
			this->Transform.Rotate(TransformMatrix::GetForward(), glm::radians(5.0f));
		}
		else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_D))
		{
			this->Transform.Rotate(TransformMatrix::GetForward(), glm::radians(-5.0f));
		}
		else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_W))
		{
			glm::vec3 pos = euler * 0.1f * TransformMatrix::GetUp();
			this->Transform.Translate(glm::vec3((float)sin(pos.x)*0.1f, (float)cos(pos.x)*0.1f, 0.0f));
		}
		else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_SPACE) && bulletObject == nullptr)
		{
			this->bulletObject = new BulletObject();
			bulletObject->Transform.SetMatrix(this->Transform.GetMatrix());
		}
	}

	void ShipObject::Update()
	{
		if (bulletObject != nullptr)
			bulletObject->Update();
	}

	void ShipObject::Render(Camera cam)
	{
		Singleton::getInstance()->GetTM()->GetTexture(0)->Bind();
		this->model->LinkShader();
		this->model->Bind();
		glUseProgram(this->model->GetShaderID());
		GLint uniformLoc = glGetUniformLocation(this->model->GetShaderID(), "renderType");
		GLint worldMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "WorldMatrix");
		GLint shapeColorLoc = glGetUniformLocation(this->model->GetShaderID(), "shapeColour");
		GLint viewMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "ViewMatrix");
		GLint projectMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "ProjectionMatrix");
		glProgramUniform1i(this->model->GetShaderID(), uniformLoc, 0);
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(this->Transform.GetMatrix()));
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(cam.GetViewMatrix()));
		glUniformMatrix4fv(projectMatrixLoc, 1, GL_FALSE, glm::value_ptr(cam.GetProjectionMatrix()));
		glUniform3f(shapeColorLoc, 0.0f, 0.0f, 0.0f);
		this->model->Render();
		this->model->Unbind();
		this->model->DetachShader();
		Singleton::getInstance()->GetTM()->GetTexture(0)->Unbind();

		if (bulletObject != nullptr)
			bulletObject->Render(cam);
	}
}
