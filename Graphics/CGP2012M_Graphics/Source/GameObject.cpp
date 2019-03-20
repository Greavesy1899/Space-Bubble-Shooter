#include "GameObject.h"
#include <algorithm>

namespace EngineOpenGL
{
	GameObject::GameObject()
	{
		this->isHidden = false;
	}

	GameObject::GameObject(OBJLoader loader, ObjectTypes type)
	{
		this->objectType = type;
		this->isHidden = false;
		this->model = new Model();
		this->model->SetModelToObj(loader);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->Transform = TransformMatrix();
	}

	GameObject::GameObject(float width, float height, ObjectTypes type)
	{
		this->objectType = type;
		this->isHidden = false;
		this->model = new Model();
		this->model->SetModelToSquare(width, height);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->Transform = TransformMatrix();
	}

	GameObject::GameObject(float radiusFactor, ObjectTypes type)
	{
		this->objectType = type;
		this->isHidden = false;
		this->model = new Model();
		this->model->SetModelToCircle(radiusFactor);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->Transform = TransformMatrix();
	}

	GameObject::~GameObject()
	{
		delete this->model;
	}

	bool GameObject::IsHidden() const
	{
		return this->isHidden;
	}

	void GameObject::HideObject(bool b)
	{
		this->isHidden = b;
	}

	void EngineOpenGL::GameObject::Input()
	{
	}

	void EngineOpenGL::GameObject::Update()
	{
	}

	void EngineOpenGL::GameObject::Render(Camera cam)
	{
		if (isHidden)
			return;

		if(this->renderType == RenderTypes::TEXTURE || this->renderType == RenderTypes::SPECIAL_BUBBLE)
			Singleton::getInstance()->GetTM()->GetTexture(this->textureID)->Bind();

		this->model->LinkShader();
		this->model->Bind();
		glUseProgram(this->model->GetShaderID());
		this->model->GetShader()->SetUniformMatrix("WorldMatrix", this->Transform.GetMatrix());
		this->model->GetShader()->SetUniformMatrix("ViewMatrix", cam.GetViewMatrix());
		this->model->GetShader()->SetUniformMatrix("ProjectionMatrix", cam.GetProjectionMatrix());
		this->model->GetShader()->SetUniformInt("renderType", this->renderType);
		this->model->GetShader()->SetUniformFloat("shapeColour", this->colour.r, this->colour.g, this->colour.b);
		this->model->Render();
		this->model->Unbind();
		this->model->DetachShader();

		if (this->renderType == RenderTypes::TEXTURE || this->renderType == RenderTypes::SPECIAL_BUBBLE)
			Singleton::getInstance()->GetTM()->GetTexture(this->textureID)->Unbind();
	}

	void GameObject::SetRenderType(RenderTypes type)
	{
		this->renderType = type;
	}

	void GameObject::SetDiffuseColour(glm::vec3 colour)
	{
		this->colour = colour;
	}

	void GameObject::SetTextureID(int id)
	{
		this->textureID = id;
	}

	void GameObject::SetObjectType(ObjectTypes type)
	{
		this->objectType = type;
	}

	RenderTypes GameObject::GetRenderType() const
	{
		return this->renderType;
	}

	Model * EngineOpenGL::GameObject::GetModel()
	{
		return this->model;
	}
	bool GameObject::IsCircleBoxColliding(GameObject * rect, GameObject * circle)
	{
		glm::vec3 rectPos = rect->Transform.GetPosition();
		glm::vec3 circlePos = circle->Transform.GetPosition();

		ModelBounds newBBox1 = ModelBounds(rectPos + rect->GetModel()->GetBounds().GetMinimum(), rectPos + rect->GetModel()->GetBounds().GetMaximum());
		ModelBounds newBBox2 = ModelBounds(circlePos + circle->GetModel()->GetBounds().GetMinimum(), circlePos + circle->GetModel()->GetBounds().GetMaximum());

		GLfloat distX = circlePos.x - std::max(rectPos.x, std::min(circlePos.x, rectPos.x + rect->GetModel()->GetBounds().GetWidth()));
		GLfloat distY = circlePos.y - std::max(rectPos.y, std::min(circlePos.y, rectPos.y + rect->GetModel()->GetBounds().GetHeight()));
		GLfloat magnitude = (distX * distX + distY * distY);
		GLfloat radius = rect->GetModel()->GetBounds().GetRadius() * circle->GetModel()->GetBounds().GetRadius();
		bool isCircleIntersection = magnitude < radius;
		bool isBBoxColliding = (newBBox1.GetMinimum().x < newBBox2.GetMaximum().x) && 
							   (newBBox1.GetMaximum().x > newBBox2.GetMinimum().x) &&
			                   (newBBox1.GetMinimum().y < newBBox2.GetMaximum().y) && 
			                   (newBBox1.GetMaximum().y > newBBox2.GetMinimum().y);

		return isBBoxColliding && isCircleIntersection;
	}

	bool GameObject::IsBoxColliding(GameObject * obj1, GameObject * obj2)
	{
		glm::vec3 rect1Pos = obj1->Transform.GetPosition();
		glm::vec3 rect2Pos = obj2->Transform.GetPosition();

		ModelBounds newBBox1 = ModelBounds(rect1Pos + obj1->GetModel()->GetBounds().GetMinimum(), rect1Pos + obj1->GetModel()->GetBounds().GetMaximum());
		ModelBounds newBBox2 = ModelBounds(rect2Pos + obj2->GetModel()->GetBounds().GetMinimum(), rect2Pos + obj2->GetModel()->GetBounds().GetMaximum());

		bool isBBoxColliding = (newBBox1.GetMinimum().x < newBBox2.GetMaximum().x) &&
			(newBBox1.GetMaximum().x > newBBox2.GetMinimum().x) &&
			(newBBox1.GetMinimum().y < newBBox2.GetMaximum().y) &&
			(newBBox1.GetMaximum().y > newBBox2.GetMinimum().y);

		return isBBoxColliding;
	}
}
