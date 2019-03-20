#include "BubbleObject.h"

namespace EngineOpenGL
{
	BubbleObject::BubbleObject()
	{
	}
	BubbleObject::BubbleObject(OBJLoader loader)
	{
		this->model = new Model();
		this->model->SetModelToObj(loader);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->xDirection = rand() % 360;
		this->yDirection = rand() % 360;
		this->shapeColour = glm::vec3(0.0f, 1.0f, 0.0f);		

		//sort out random scaling.
		float randScale = (float)rand() / RAND_MAX;
		
		if (randScale < 0.5f)
			randScale = 0.5f;

		this->Transform.SetScale(glm::vec3(randScale));
		this->model->UpdateModelBounds(this->Transform.GetScale());
		this->renderType = RenderTypes::SPECIAL_BUBBLE;
		this->textureID = 1;
	}

	BubbleObject::~BubbleObject()
	{
		delete this->model;
	}

	void BubbleObject::Update()
	{
		//CheckBounds();
		this->Transform.Translate(glm::vec3((float)sin(xDirection)*0.01f, (float)sin(yDirection)*0.01f, 0.0f));
	}
	void BubbleObject::InvertDirection()
	{
		this->xDirection = -this->xDirection;
		this->yDirection = -this->yDirection;
	}
}