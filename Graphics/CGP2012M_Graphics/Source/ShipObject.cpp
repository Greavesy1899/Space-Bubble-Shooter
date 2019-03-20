#include "ShipObject.h"

namespace EngineOpenGL
{
	bool ShipObject::CheckBounds()
	{
		return false;
	}

	void ShipObject::LookAt()
	{
	}

	ShipObject::ShipObject()
	{
		this->model = new Model();
		this->model->SetModelToSquare(0.2f, 0.2f);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->textureID = 0;
		this->renderType = RenderTypes::TEXTURE;
		this->lives = 3;
		this->movingForward = false;
	}

	ShipObject::~ShipObject()
	{
		delete this->model;
	}

	void ShipObject::Input()
	{	
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
			glm::vec3 euler = this->Transform.GetEuler();
			glm::vec3 pos = euler * 0.1f * TransformMatrix::GetUp();
			this->Transform.Translate(glm::vec3((float)sin(pos.x)*0.1f, (float)cos(pos.x)*0.1f, 0.0f));
		}
	}

	void ShipObject::Update()
	{
	}

	int ShipObject::GetLives() const
	{
		return this->lives;
	}
	bool ShipObject::HasMoved() const
	{
		return this->movingForward;
	}
	void ShipObject::DeincrementLife()
	{
		if(lives != 0)
			this->lives--;
	}
}
