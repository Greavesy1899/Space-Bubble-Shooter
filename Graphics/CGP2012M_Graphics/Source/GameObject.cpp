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

	void GameObject::Input()
	{
	}

	void GameObject::Update()
	{
	}

	void GameObject::Render(Camera cam, LightObject light)
	{
		if (isHidden)
			return;

		if (this->renderType == RenderTypes::TEXTURE || this->renderType == RenderTypes::SPECIAL_BUBBLE)
		{
			Singleton::getInstance()->GetTM()->GetTexture(this->textureID)->Bind();
		}	
		else if ((this->renderType == RenderTypes::SPECIAL_SKYBOX))
		{
			Singleton::getInstance()->GetTM()->GetTexture(this->textureID)->Bind();
			glDepthMask(GL_FALSE);
		}

		this->model->LinkShader();
		this->model->Bind();
		glUseProgram(this->model->GetShaderID());
		this->model->GetShader()->SetUniformMatrix("WorldMatrix", this->Transform.GetMatrix());
		this->model->GetShader()->SetUniformMatrix("ViewMatrix", cam.GetViewMatrix());

		if (this->renderType != RenderTypes::SPECIAL_SKYBOX)
		{
			glm::vec3 direction = light.GetDirectLight().direction;
			glm::vec3 colour = light.GetDirectLight().colour;
			GLfloat intensity = light.GetDirectLight().intensity;
			this->model->GetShader()->SetUniformFloat("dLight.direction", direction.x, direction.y, direction.z);
			this->model->GetShader()->SetUniformFloat("dLight.colour", colour.r, colour.g, colour.b);

			for (int i = 0; i < 3; i++)
			{
				std::string start = "pLights[" + std::to_string(i) + "].";
				this->model->GetShader()->SetUniformFloat(start +"position", light.GetPointLight(i).position.x, light.GetPointLight(i).position.y, light.GetPointLight(i).position.z);
				this->model->GetShader()->SetUniformFloat(start + "ambient", light.GetPointLight(i).ambient.x, light.GetPointLight(i).ambient.y, light.GetPointLight(i).ambient.z);
				this->model->GetShader()->SetUniformFloat(start + "diffuse", light.GetPointLight(i).diffuse.x, light.GetPointLight(i).diffuse.y, light.GetPointLight(i).diffuse.z);
				this->model->GetShader()->SetUniformFloat(start + "constant", light.GetPointLight(i).constant);
				this->model->GetShader()->SetUniformFloat(start + "quadratic", light.GetPointLight(i).quadratic);
				this->model->GetShader()->SetUniformFloat(start + "linear", light.GetPointLight(i).linear);
			}

			this->model->GetShader()->SetUniformFloat("viewPos", cam.ViewMatrix.GetPosition().x, cam.ViewMatrix.GetPosition().y, cam.ViewMatrix.GetPosition().z);
		}

		this->model->GetShader()->SetUniformMatrix("ProjectionMatrix", cam.GetProjectionMatrix());
		this->model->GetShader()->SetUniformInt("renderType", this->renderType);
		this->model->GetShader()->SetUniformFloat("shapeColour", this->colour.r, this->colour.g, this->colour.b);
		this->model->Render();
		this->model->Unbind();
		this->model->DetachShader();

		if (this->renderType == RenderTypes::TEXTURE || this->renderType == RenderTypes::SPECIAL_BUBBLE)
		{
			Singleton::getInstance()->GetTM()->GetTexture(this->textureID)->Unbind();
		}
		else if ((this->renderType == RenderTypes::SPECIAL_SKYBOX))
		{
			Singleton::getInstance()->GetTM()->GetTexture(this->textureID)->Bind();
			glDepthMask(GL_TRUE);
		}
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

	void GameObject::SetShaderType(ShaderProgram* sp)
	{
		this->model->SetShader(sp);
	}

	RenderTypes GameObject::GetRenderType() const
	{
		return this->renderType;
	}

	Model * EngineOpenGL::GameObject::GetModel()
	{
		return this->model;
	}

	bool GameObject::IsCircleBoxColliding(GameObject* rect, GameObject* circle)
	{
		glm::vec3 rectPos = rect->Transform.GetPosition();
		glm::vec3 rectMin = rect->Transform.GetMatrix() * glm::vec4(rect->GetModel()->GetBounds().GetMinimum(), 1.0f);
		glm::vec3 rectMax = rect->Transform.GetMatrix() * glm::vec4(rect->GetModel()->GetBounds().GetMaximum(), 1.0f);
		glm::vec3 circlePos = circle->Transform.GetPosition();
		glm::vec3 circleMin = circle->Transform.GetMatrix() * glm::vec4(circle->GetModel()->GetBounds().GetMinimum(), 1.0f);
		glm::vec3 circleMax = circle->Transform.GetMatrix() * glm::vec4(circle->GetModel()->GetBounds().GetMaximum(), 1.0f);
		GLfloat distX = circlePos.x - std::max(rectPos.x, std::min(circlePos.x, rectPos.x + rect->GetModel()->GetBounds().GetWidth()));
		GLfloat distY = circlePos.y - std::max(rectPos.y, std::min(circlePos.y, rectPos.y + rect->GetModel()->GetBounds().GetHeight()));
		GLfloat magnitude = (distX * distX + distY * distY);
		GLfloat radius = circle->GetModel()->GetBounds().GetRadius();
		bool isCircleIntersection = magnitude < radius;
		bool bboxX = rectMin.x < circleMax.x && rectMax.x > circleMin.x;
		bool bboxY = rectMin.y < circleMax.y && rectMax.y > circleMin.y;
		bool bboxZ = rectMin.z < circleMax.z && rectMax.z > circleMin.z;
		bool isBBoxColliding = bboxX && bboxY && bboxZ;
		return isCircleIntersection && isBBoxColliding;
	}

	bool GameObject::IsBoxColliding(GameObject * obj1, GameObject * obj2)
	{
		glm::vec4 rect1Min = obj1->Transform.GetMatrix() * glm::vec4(obj1->GetModel()->GetBounds().GetMinimum(), 1.0f);
		glm::vec4 rect1Max = obj1->Transform.GetMatrix() * glm::vec4(obj1->GetModel()->GetBounds().GetMaximum(), 1.0f);
		glm::vec4 rect2Min = obj2->Transform.GetMatrix() * glm::vec4(obj2->GetModel()->GetBounds().GetMinimum(), 1.0f);
		glm::vec4 rect2Max = obj2->Transform.GetMatrix() * glm::vec4(obj2->GetModel()->GetBounds().GetMaximum(), 1.0f);

		bool bboxX = rect1Min.x <= rect2Max.x && rect1Max.x >= rect2Min.x;
		bool bboxY = rect1Min.y <= rect2Max.y && rect1Max.y >= rect2Min.y;
		bool bboxZ = rect1Min.z <= rect2Max.z && rect1Max.z >= rect2Min.z;
		return bboxX && bboxY && bboxZ;
	}
}
