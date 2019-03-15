#include "GameObject.h"

namespace EngineOpenGL
{
	GameObject::GameObject()
	{
	}

	GameObject::GameObject(OBJLoader loader)
	{
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

	void EngineOpenGL::GameObject::Input()
	{
	}

	void EngineOpenGL::GameObject::Update()
	{
	}

	void EngineOpenGL::GameObject::Render(Camera cam)
	{
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

	Model * EngineOpenGL::GameObject::GetModel()
	{
		return this->model;
	}
	bool GameObject::IsColliding(GameObject * obj1, GameObject * obj2)
	{
		glm::vec3 pos1 = obj1->Transform.GetPosition();
		glm::vec3 pos2 = obj2->Transform.GetPosition();

		BoundingBox newBBox1 = BoundingBox(obj1->GetModel()->GetBBox().GetMinimum() + pos1, obj1->GetModel()->GetBBox().GetMaximum() + pos1);
		BoundingBox newBBox2 = BoundingBox(obj2->GetModel()->GetBBox().GetMinimum() + pos2, obj2->GetModel()->GetBBox().GetMaximum() + pos2);

		return (newBBox1.GetMinimum().x < newBBox2.GetMaximum().x) && (newBBox1.GetMaximum().x > newBBox2.GetMinimum().x) &&
			(newBBox1.GetMinimum().y < newBBox2.GetMaximum().y) && (newBBox1.GetMaximum().y > newBBox2.GetMinimum().y);/* &&
			(newBBox1.GetMinimum().z < newBBox2.GetMaximum().z) && (newBBox1.GetMaximum().z > newBBox2.GetMinimum().z);*/
	}
}
