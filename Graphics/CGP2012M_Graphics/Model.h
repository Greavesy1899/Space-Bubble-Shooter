#ifndef MODEL
#define MODEL

#include <GL/glew.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

class Model
{
	GLfloat vertices[18];

public:
	Model();
	~Model();

	bool Init();
	bool Unbind();
	bool Bind();
	bool Build();
	bool Render();

	GLuint vBuffer;
	GLuint vArray;
};

#endif

