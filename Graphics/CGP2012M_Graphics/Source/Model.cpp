#include "Model.h"

namespace EngineOpenGL
{
	Model::Model()
	{
		this->shader = Singleton::getInstance()->GetSM()->GetShader(0);
		isObj = false;
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

	bool Model::SetModelToCube(GLfloat widthFactor, GLfloat heightFactor, GLfloat depthFactor)
	{
		//indices
		this->indices = new GLushort[36];
		this->indices[0] = 0;
		this->indices[1] = 2;
		this->indices[2] = 3;

		this->indices[3] = 3;
		this->indices[4] = 1;
		this->indices[5] = 0;

		this->indices[6] = 4;
		this->indices[7] = 5;
		this->indices[8] = 7;

		this->indices[9] = 7;
		this->indices[10] = 6;
		this->indices[11] = 4;

		this->indices[12] = 0;
		this->indices[13] = 1;
		this->indices[14] = 5;

		this->indices[15] = 5;
		this->indices[16] = 4;
		this->indices[17] = 0;

		this->indices[18] = 1;
		this->indices[19] = 3;
		this->indices[20] = 7;

		this->indices[21] = 7;
		this->indices[22] = 5;
		this->indices[23] = 1;

		this->indices[24] = 3;
		this->indices[25] = 2;
		this->indices[26] = 6;

		this->indices[27] = 6;
		this->indices[28] = 7;
		this->indices[29] = 3;

		this->indices[30] = 2;
		this->indices[31] = 0;
		this->indices[32] = 4;

		this->indices[33] = 4;
		this->indices[34] = 6;
		this->indices[35] = 2;

		//vertices
		this->vertices = new VertexLayout[8];
		this->vertices[0] = VertexLayout(glm::vec3(-widthFactor, -heightFactor, depthFactor), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f));
		this->vertices[1] = VertexLayout(glm::vec3(widthFactor, -heightFactor, depthFactor), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
		this->vertices[2] = VertexLayout(glm::vec3(-widthFactor, -heightFactor, -depthFactor), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f));
		this->vertices[3] = VertexLayout(glm::vec3(widthFactor, -heightFactor, -depthFactor), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		this->vertices[4] = VertexLayout(glm::vec3(-widthFactor, heightFactor, depthFactor), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f));
		this->vertices[5] = VertexLayout(glm::vec3(widthFactor, heightFactor, depthFactor), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
		this->vertices[6] = VertexLayout(glm::vec3(-widthFactor, heightFactor, -depthFactor), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f));
		this->vertices[7] = VertexLayout(glm::vec3(widthFactor, heightFactor, -depthFactor), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f));

		this->numTriangles = 12;
		this->numVertices = 8;
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
		
		GLushort indCount = loader.indices.size() / 3;
		this->numTriangles = (GLushort)indCount / 6;
		this->numVertices = numTriangles;
		this->vertices = new VertexLayout[indCount];
		this->indices = new GLushort[indCount];


		//vertices
		GLushort intIDX = 0;
		for (int i = 0; i != loader.indices.size(); i+=3)
		{
			VertexLayout vertex = VertexLayout();
			vertex.position = loader.vertices[loader.indices[i + 0]];
			vertex.uv = loader.texCoords[loader.indices[i + 1]];
			vertex.normal = loader.normals[loader.indices[i + 2]];
			vertex.color = glm::vec3(1.0f);
			this->vertices[intIDX] = vertex;
			this->indices[intIDX] = loader.indices[i];
			intIDX++;
		}

		UpdateModelBounds();
		this->isObj = true;
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
		int mult = (this->isObj ? 1 : 6);
		glBufferData(GL_ARRAY_BUFFER, this->numVertices * sizeof(VertexLayout), this->vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numTriangles * mult, this->indices, GL_STATIC_DRAW);
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
		if (isObj)
			glDrawArrays(GL_TRIANGLES, 0, this->numVertices * sizeof(VertexLayout));
		else
			glDrawElements(GL_TRIANGLES, this->numTriangles*3, GL_UNSIGNED_SHORT, 0);

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