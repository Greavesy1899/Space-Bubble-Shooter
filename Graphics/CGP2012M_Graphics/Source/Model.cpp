#include "Model.h"

namespace EngineOpenGL
{
	Model::Model()
	{
		this->shader = Singleton::getInstance()->GetSM()->GetShader(1);
		this->transform = glm::mat4(1.0f);
	}

	Model::~Model()
	{
		glDeleteBuffers(1, &this->vbo);
		glDeleteBuffers(1, &this->ibo);
		glDeleteVertexArrays(1, &this->vao);
		delete[] this->indices;
		delete[] this->vertices;
	}

	bool Model::SetVertices(VertexLayout* vl, GLuint numVertices)
	{
		this->vertices = vl;
		this->numVertices = numVertices;
		return true;
	}

	bool Model::SetIndices(GLushort* inds, GLuint numTriangles)
	{
		this->indices = inds;
		this->numTriangles = numTriangles;
		return true;
	}

	bool Model::SetModelToSquare(GLfloat widthFactor, GLfloat heightFactor)
	{

		//indices
		this->indices = new GLushort[6];
		this->indices[0] = 1;
		this->indices[1] = 0;
		this->indices[2] = 2;
		this->indices[3] = 2;
		this->indices[4] = 3;
		this->indices[5] = 0;

		//vertices
		this->vertices = new VertexLayout[4];
		this->vertices[0] = VertexLayout(widthFactor, heightFactor, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		this->vertices[1] = VertexLayout(widthFactor, -heightFactor, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		this->vertices[2] = VertexLayout(-widthFactor, -heightFactor, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
		this->vertices[3] = VertexLayout(-widthFactor, heightFactor, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		this->numTriangles = 2;
		this->numVertices = 4;
		return true;
	}

	bool Model::SetModelToCircle(GLfloat radiusFactor)
	{
		this->vertices = new VertexLayout[30];
		this->indices = new GLushort[87];
		this->numVertices = 30;
		this->numTriangles = 87;

		GLint ind = 1;
		for (int i = 0; i != 87; i+=3)
		{
			this->indices[i] = 0;
			this->indices[i + 1] = ind;
			this->indices[i + 2] = ++ind;
		}

		this->vertices[0] = VertexLayout(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		GLfloat angle = 0.0f;

		for (int i = 1; i != 30; i++)
		{
			this->vertices[i] = VertexLayout((radiusFactor * cos(angle)), radiusFactor * sin(angle), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			angle += (2 * 3.141) / 28.0f;
		}
		return true;
	}

	bool Model::SetTransform(glm::vec3 translate, glm::vec3 scale, glm::vec3 rotation)
	{
		this->transform = glm::translate(this->transform, translate);
		this->transform = glm::scale(this->transform, scale);
		this->transform = glm::rotate(this->transform, 0.0f, rotation);
		return true;
	}

	glm::mat4 Model::GetTransform() const
	{
		return this->transform;
	}

	GLuint Model::GetShaderID() const
	{
		return this->shader->GetProgramID();
	}

	bool Model::Init()
	{
		glGenBuffers(1, &this->vbo);
		glGenBuffers(1, &this->ibo);
		glGenVertexArrays(1, &this->vao);
		return true;
	}

	bool Model::Unbind()
	{
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		return true;
	}

	bool Model::Bind()
	{
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		return true;
	}

	bool Model::Build()
	{
		glBufferData(GL_ARRAY_BUFFER, this->numVertices * sizeof(VertexLayout), this->vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numTriangles * 6, this->indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)(2*sizeof(glm::vec3)));
		glEnableVertexAttribArray(2);
		return true;
	}

	bool Model::Render()
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, this->numTriangles * 3, GL_UNSIGNED_SHORT, 0);
		return true;
	}

	bool Model::LinkShader() const
	{
		this->shader->Attach();
		this->shader->Link();
		return true;
	}

	bool Model::DetachShader() const
	{
		this->shader->Detach();
		return true;
	}

	Model::VertexLayout::VertexLayout()
	{
		this->position = glm::vec3();
		this->color = glm::vec3();
		this->uv = glm::vec2();
	}

	Model::VertexLayout::VertexLayout(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat u, GLfloat v)
	{
		this->position = glm::vec3(x, y, z);
		this->color = glm::vec3(r, g, b);
		this->uv = glm::vec2(u, v);
	}
}