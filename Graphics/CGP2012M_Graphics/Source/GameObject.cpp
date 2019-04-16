#include "GameObject.h"
#include <algorithm>

namespace EngineOpenGL
{
	GameObject::GameObject()
	{
		this->isHidden = false;
		this->model = nullptr;
		this->Transform = TransformMatrix();
		this->objectType = ObjectTypes::BASIC;
		this->colour = glm::vec3(1.0f);
		this->renderType = RenderTypes::COLOUR;
		this->textureID = -1;
	}

	GameObject::GameObject(OBJLoader loader, ObjectTypes type)
	{
		this->objectType = type;
		this->isHidden = false;
		this->Transform = TransformMatrix();
		this->colour = glm::vec3(1.0f);
		this->renderType = RenderTypes::COLOUR;
		this->textureID = -1;
		this->model = new Model();
		this->model->SetModelToObj(loader);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
	}

	GameObject::GameObject(float width, float height, ObjectTypes type)
	{
		this->objectType = type;
		this->isHidden = false;
		this->Transform = TransformMatrix();
		this->colour = glm::vec3(1.0f);
		this->renderType = RenderTypes::COLOUR;
		this->textureID = -1;
		this->model = new Model();
		this->model->SetModelToSquare(width, height);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->Transform = TransformMatrix();
	}

	GameObject::GameObject(float width, float height, float depth, ObjectTypes type)
	{
		this->objectType = type;
		this->isHidden = false;
		this->Transform = TransformMatrix();
		this->colour = glm::vec3(1.0f);
		this->renderType = RenderTypes::COLOUR;
		this->textureID = -1;
		this->model = new Model();
		this->model->SetModelToCube(width, height, depth);
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
		this->model->GetShader()->SetUniformFloat("lightPos", cam.ViewMatrix.GetPosition().x, cam.ViewMatrix.GetPosition().y, cam.ViewMatrix.GetPosition().z);
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
		glm::vec3 rectMin = rect->Transform.GetMatrix() * glm::vec4(rect->GetModel()->GetBounds().GetMinimum(), 1.0f);
		glm::vec3 rectMax = rect->Transform.GetMatrix() * glm::vec4(rect->GetModel()->GetBounds().GetMaximum(), 1.0f);
		glm::vec3 circlePos = rect->Transform.GetPosition();
		glm::vec3 circleMin = circle->Transform.GetMatrix() * glm::vec4(circle->GetModel()->GetBounds().GetMinimum(), 1.0f);
		glm::vec3 circleMax = circle->Transform.GetMatrix() * glm::vec4(circle->GetModel()->GetBounds().GetMaximum(), 1.0f);
		
		ModelBounds newBBox1 = ModelBounds(glm::vec3(rectMin), glm::vec3(rectMax));
		ModelBounds newBBox2 = ModelBounds(glm::vec3(circleMin), glm::vec3(circleMax));

		GLfloat distX = circlePos.x - std::max(rectPos.x, std::min(circlePos.x, rectPos.x + rect->GetModel()->GetBounds().GetWidth()));
		GLfloat distY = circlePos.y - std::max(rectPos.y, std::min(circlePos.y, rectPos.y + rect->GetModel()->GetBounds().GetHeight()));
		GLfloat magnitude = (distX * distX + distY * distY);
		GLfloat radius = rect->GetModel()->GetBounds().GetRadius() * circle->GetModel()->GetBounds().GetRadius();
		bool isCircleIntersection = magnitude < radius;
		bool isBBoxColliding = (newBBox1.GetMinimum().x < newBBox2.GetMaximum().x) &&
			(newBBox1.GetMaximum().x > newBBox2.GetMinimum().x) &&
			(newBBox1.GetMinimum().y < newBBox2.GetMaximum().y) &&
			(newBBox1.GetMaximum().y > newBBox2.GetMinimum().y) &&
			(newBBox1.GetMinimum().z < newBBox2.GetMaximum().z) &&
			(newBBox1.GetMaximum().z > newBBox2.GetMinimum().z);

		return isBBoxColliding && isCircleIntersection;
	}

	bool GameObject::IsBoxColliding(GameObject * obj1, GameObject * obj2)
	{
		glm::vec4 rect1Min = obj1->Transform.GetMatrix() * glm::vec4(obj1->GetModel()->GetBounds().GetMinimum(), 1.0f);
		glm::vec4 rect1Max = obj1->Transform.GetMatrix() * glm::vec4(obj1->GetModel()->GetBounds().GetMaximum(), 1.0f);
		glm::vec4 rect2Min = obj2->Transform.GetMatrix() * glm::vec4(obj2->GetModel()->GetBounds().GetMinimum(), 1.0f);
		glm::vec4 rect2Max = obj2->Transform.GetMatrix() * glm::vec4(obj2->GetModel()->GetBounds().GetMaximum(), 1.0f);

		ModelBounds newBBox1 = ModelBounds(glm::vec3(rect1Min), glm::vec3(rect1Max));
		ModelBounds newBBox2 = ModelBounds(glm::vec3(rect2Min), glm::vec3(rect2Max));

		bool bboxX = newBBox1.GetMinimum().x < newBBox2.GetMaximum().x && (newBBox1.GetMaximum().x > newBBox2.GetMinimum().x);
		bool bboxY = newBBox1.GetMinimum().y < newBBox2.GetMaximum().y && (newBBox1.GetMaximum().y > newBBox2.GetMinimum().y);
		bool bboxZ = newBBox1.GetMinimum().z < newBBox2.GetMaximum().z && (newBBox1.GetMaximum().z > newBBox2.GetMinimum().z);
		bool isBBoxColliding = bboxX && bboxY && bboxZ;

		
		return isBBoxColliding;
	}
}
