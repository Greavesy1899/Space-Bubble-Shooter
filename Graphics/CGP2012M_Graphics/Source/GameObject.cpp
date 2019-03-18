#include "GameObject.h"
#include <algorithm>

namespace EngineOpenGL
{
	GameObject::GameObject()
	{
		this->isHidden = false;
	}

	GameObject::GameObject(OBJLoader loader)
	{
		this->isHidden = false;
		this->model = new Model();
		this->model->SetModelToObj(loader);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->Transform = TransformMatrix();
	}

	GameObject::GameObject(float width, float height)
	{
		this->isHidden = false;
		this->model = new Model();
		this->model->SetModelToSquare(width, height);
		this->model->Init();
		this->model->Bind();
		this->model->Build();
		this->model->Unbind();
		this->Transform = TransformMatrix();
	}

	GameObject::GameObject(float radiusFactor)
	{
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

		if(this->textureID > 0 && this->textureID < Singleton::getInstance()->GetTM()->GetSize())
			Singleton::getInstance()->GetTM()->GetTexture(this->textureID)->Bind();

		this->model->LinkShader();
		this->model->Bind();
		glUseProgram(this->model->GetShaderID());
		GLint uniformLoc = glGetUniformLocation(this->model->GetShaderID(), "renderType");
		GLint worldMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "WorldMatrix");
		GLint shapeColorLoc = glGetUniformLocation(this->model->GetShaderID(), "shapeColour");
		GLint viewMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "ViewMatrix");
		GLint projectMatrixLoc = glGetUniformLocation(this->model->GetShaderID(), "ProjectionMatrix");
		glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(this->Transform.GetMatrix()));
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(cam.GetViewMatrix()));
		glUniformMatrix4fv(projectMatrixLoc, 1, GL_FALSE, glm::value_ptr(cam.GetProjectionMatrix()));

		glProgramUniform1i(this->model->GetShaderID(), uniformLoc, this->renderType);
		glUniform3f(shapeColorLoc, colour.r, colour.g, colour.b);

		this->model->Render();
		this->model->Unbind();
		this->model->DetachShader();

		if (this->textureID > 0 && this->textureID < Singleton::getInstance()->GetTM()->GetSize())
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

	RenderTypes GameObject::GetRenderType() const
	{
		return this->renderType;
	}

	Model * EngineOpenGL::GameObject::GetModel()
	{
		return this->model;
	}
	bool GameObject::IsColliding(GameObject * rect, GameObject * circle)
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
}
