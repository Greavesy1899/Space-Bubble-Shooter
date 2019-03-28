#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TextureClass.h"
#include "SingletonManager.h"
#include "ShaderProgram.h"
#include "ModelBounds.h"
#include "TransformMatrix.h"
#include "OBJLoader.h"

namespace EngineOpenGL
{
	class Model
	{
	public:
		struct VertexLayout
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 color;
			glm::vec2 uv;

			VertexLayout();
			VertexLayout(GLfloat px, GLfloat py, GLfloat pz, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat r, GLfloat g, GLfloat b, GLfloat u, GLfloat v);
			VertexLayout(glm::vec3 pos, glm::vec3 nor, glm::vec3 color, glm::vec2 uv);
		};

	private:
		VertexLayout* vertices;
		GLushort* indices;
		TextureClass* texture;
		ShaderProgram* shader;
		GLuint numVertices;
		GLuint numTriangles;
		GLuint vbo;
		GLuint ibo;
		GLuint vao;
		ModelBounds bounds;

	public:
		Model();
		~Model();

		bool Init();
		bool SetVertices(VertexLayout* vl, GLuint numVertices);
		bool SetIndices(GLushort* inds, GLuint numTringles);
		bool SetModelToSquare(GLfloat widthFactor, GLfloat heightFactor);
		bool SetModelToCircle(GLfloat radiusFactor);
		bool SetModelToObj(OBJLoader loader);
		void UpdateModelBounds(glm::vec3 scale = glm::vec3(1.0f));

		GLuint GetShaderID() const;
		ModelBounds GetBounds() const;
		GLuint GetNumVertices() const;
		GLuint GetNumTriangles() const;

		bool Unbind();
		bool Bind();
		bool Build();
		bool Render();
		ShaderProgram* GetShader() const;
		bool LinkShader() const;
		bool DetachShader() const;
	};
}
#endif

