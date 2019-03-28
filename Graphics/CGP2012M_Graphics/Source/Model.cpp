#include "Model.h"

namespace EngineOpenGL
{
	Model::Model()
	{
		this->shader = Singleton::getInstance()->GetSM()->GetShader(0);
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
		UpdateModelBounds();
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
		this->vertices[0] = VertexLayout(widthFactor, heightFactor, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		this->vertices[1] = VertexLayout(widthFactor, -heightFactor, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		this->vertices[2] = VertexLayout(-widthFactor, -heightFactor, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
		this->vertices[3] = VertexLayout(-widthFactor, heightFactor, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		this->numTriangles = 2;
		this->numVertices = 4;
		UpdateModelBounds();
		return true;
	}

	bool Model::SetModelToCircle(GLfloat radiusFactor)
	{
		this->vertices = new VertexLayout[30];
		this->indices = new GLushort[87];
		this->numVertices = 30;
		this->numTriangles = 29;

		GLint ind = 1;
		for (int i = 0; i != 87; i+=3)
		{
			this->indices[i] = 0;
			this->indices[i + 1] = ind;
			this->indices[i + 2] = ++ind;
		}

		this->vertices[0] = VertexLayout(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		GLfloat angle = 0.0f;

		for (int i = 1; i != 30; i++)
		{
			glm::vec3 pos = glm::vec3(radiusFactor * cos(angle), radiusFactor * sin(angle), 0.0f);
			glm::vec3 col = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 nor = glm::vec3(1.0f, 1.0f, 1.0f);
			glm::vec2 uv = glm::vec2(((radiusFactor * cos(angle))*0.5f) + 0.75f, ((radiusFactor * sin(angle))*0.75f) + 0.5f);

			this->vertices[i] = VertexLayout(pos, nor, col, uv);
			angle += (2 * 3.141) / (GLfloat)28.0f;
		}
		UpdateModelBounds();
		return true;
	}

	bool Model::SetModelToObj(OBJLoader loader)
	{
		this->vertices = new VertexLayout[loader.vertices.size()];
		this->numVertices = loader.vertices.size();
		this->numTriangles = (GLushort)loader.indices.size()/3;
		this->indices = new GLushort[loader.indices.size()];

		for (int i = 0; i != loader.vertices.size(); i++)
		{
			VertexLayout vertex = VertexLayout();
			vertex.position = loader.vertices[i];
			vertex.color = glm::vec3(1.0f);
			vertex.uv = loader.texCoords[i];
			this->vertices[i] = vertex;
		}

		for (int i = 0; i != loader.indices.size(); i++)
		{
			this->indices[i] = loader.indices[i];
		}

		UpdateModelBounds();

		return true;
	}

	void Model::UpdateModelBounds(glm::vec3 scale)
	{
		glm::vec3 min(0);
		glm::vec3 max(0);

		for (int i = 0; i != this->numVertices; i++)
		{
			glm::vec3 pos = this->vertices[i].position;

			if (pos.x < min.x)
				min.x = pos.x;

			if (pos.x > max.x)
				max.x = pos.x;

			if (pos.y < min.y)
				min.y = pos.y;

			if (pos.y > max.y)
				max.y = pos.y;

			if (pos.z < min.z)
				min.z = pos.z;

			if (pos.z > max.z)
				max.z = pos.z;
		}

		this->bounds = ModelBounds(min*scale, max*scale);
	}

	GLuint Model::GetShaderID() const
	{
		return this->shader->GetProgramID();
	}

	ModelBounds Model::GetBounds() const
	{
		return this->bounds;
	}

	GLuint Model::GetNumVertices() const
	{
		return this->numVertices;
	}

	GLuint Model::GetNumTriangles() const
	{
		return this->numTriangles;
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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numTriangles*6, this->indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)(2*sizeof(glm::vec3)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexLayout), (GLvoid*)(3*sizeof(glm::vec3)));
		glEnableVertexAttribArray(3);
		return true;
	}

	bool Model::Render()
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, this->numTriangles * 3, GL_UNSIGNED_SHORT, 0);
		return true;
	}

	ShaderProgram * Model::GetShader() const
	{
		return this->shader;
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

	Model::VertexLayout::VertexLayout(GLfloat px, GLfloat py, GLfloat pz, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat r, GLfloat g, GLfloat b, GLfloat u, GLfloat v)
	{
		this->position = glm::vec3(px, py, pz);
		this->normal = glm::vec3(nx, ny, nz);
		this->color = glm::vec3(r, g, b);
		this->uv = glm::vec2(u, v);
	}
	Model::VertexLayout::VertexLayout(glm::vec3 pos, glm::vec3 nor, glm::vec3 color, glm::vec2 uv)
	{
		this->position = pos;
		this->normal = nor;
		this->color = color;
		this->uv = uv;
	}
}