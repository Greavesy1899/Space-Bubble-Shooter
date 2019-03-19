#include "BubbleObject.h"

namespace EngineOpenGL
{
	bool BubbleObject::CheckBounds()
	{
		ModelBounds bbox = this->model->GetBounds();
		glm::vec3 pos = this->Transform.GetPosition();

		if (pos.x + bbox.GetMinimum().x < -4.0f) {
			this->xDirection = -this->xDirection;
		}

		if (pos.y + bbox.GetMinimum().y < -4.0f) {
			this->yDirection = -this->yDirection;
		}

		if (pos.x + bbox.GetMaximum().x > 4.0f) {
			this->xDirection = -this->xDirection;
		}

		if (pos.y + bbox.GetMaximum().y > 4.0f) {
			this->yDirection = -this->yDirection;
		}

		this->Transform.Translate(glm::vec3(sin(this->xDirection)*0.01f, sin(this->yDirection)*0.01f, 0.0f));
		return true;
	}
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
		this->renderType = RenderTypes::SPECIAL_BUBBLE;
		this->textureID = 1;
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
}