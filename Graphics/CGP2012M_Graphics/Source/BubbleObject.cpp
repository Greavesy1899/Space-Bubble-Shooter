#include "BubbleObject.h"

namespace EngineOpenGL
{
	BubbleObject::BubbleObject()
	{
		this->xDirection = 0;
		this->yDirection = 0;

	}
	BubbleObject::BubbleObject(OBJLoader loader)
	{
		this->model = new Model();
		this->model->SetModelToObj(loader);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();	
		this->Respawn();
		this->renderType = RenderTypes::SPECIAL_BUBBLE;
		this->textureID = 1;
		this->xDirection = 0;
		this->yDirection = 0;
	}

	BubbleObject::~BubbleObject()
	{
		delete this->model;
	}

	void BubbleObject::Update()
	{
		this->Transform.Translate(glm::vec3((float)sin(xDirection)*0.033f, (float)sin(yDirection)*0.033f, 0.0f));
	}
	void BubbleObject::InvertDirection()
	{
		this->xDirection = -this->xDirection;
		this->yDirection = -this->yDirection;
	}
	void BubbleObject::Respawn()
	{
		this->xDirection = rand() % 360;
		this->yDirection = rand() % 360;
		this->colour = glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);

		//sort out random scaling.
		float randScale = (float)rand() / RAND_MAX;

		if (randScale < 0.5f)
			randScale = 0.5f;

		float randX = (float)rand() / RAND_MAX;
		float randY = (float)rand() / RAND_MAX;
		int reverseX = rand() % 2;
		int reverseY = rand() % 2;
		int multX = rand() % 5;
		int multY = rand() % 5;

		if (reverseX)
			randX -= randX;

		if (reverseY)
			randY -= randY;

		this->Transform.SetPosition(glm::vec3(randX * multX, randY * multY, 0.0f));
		this->Transform.Scale(glm::vec3(randScale));
		this->model->UpdateModelBounds(this->Transform.GetScale());
	}
}