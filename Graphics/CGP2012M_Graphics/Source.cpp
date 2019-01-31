#include <cstdio>
#include <cstdlib>
#include <iostream>

// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#include <GL/glew.h>
#include "windows.h"

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_mixer.h"
// "SDL_ttf.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"

int main(int argc, char *argv[]) {
	//SDL Initialise
	SDL_Init(SDL_INIT_EVERYTHING);

	//SDL create window
	SDL_Window *win = SDL_CreateWindow("OpenGL Window", 100, 100, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	//set context attributes
	//sets opengl version to 4.3
	int major = 4, minor = 3;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE); //use core profile
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); //ask for forward compatible
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create an OpenGL context associated with the window.
	SDL_GLContext glcontext = SDL_GL_CreateContext(win);

	//GLEW initialise
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	GLfloat verts[] = {
		-0.9f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		0.45f, 0.5f, 0.0f,

		0.0f, -0.5f, 0.0f,
		0.9f, -0.5f, 0.0f,
		0.7f, 0.5f, 0.0f
	};

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	ShaderProgram* baseShaderProgram = new ShaderProgram();
	baseShaderProgram->ReadShaderFromPath("Shaders/BaseVert.hlsl", 0);
	baseShaderProgram->ReadShaderFromPath("Shaders/BaseFrag.hlsl", 1);
	baseShaderProgram->Init();
	baseShaderProgram->Compile();
	baseShaderProgram->Attach();
	baseShaderProgram->Link();

	GLuint VBO;
	glGenBuffers(1, &VBO);
	// Initialization code using Vertex Array Object (VAO) (done once (unless the object frequently changes))
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	//bind the Vertex Array Object (VAO)
	glBindVertexArray(VAO);
	//copy the vertices array into a buffer (VBO)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	//set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Unbind the VAO
	glBindVertexArray(0);

	//*****************************
	//SDL handled input
	//Any input to the program is done here

	SDL_Event event;
	bool windowOpen = true;

	while (windowOpen)
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(baseShaderProgram->GetProgramID());
		glBindVertexArray(VAO);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		SDL_GL_SwapWindow(win);

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				windowOpen = false;
			}
		}
	}

	
	//****************************
	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
	SDL_GL_DeleteContext(glcontext);

	SDL_Quit();
	return 0;





}