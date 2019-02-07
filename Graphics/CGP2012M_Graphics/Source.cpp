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
#include "Model.h"

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

	GLushort* inds = new GLushort();
	inds[0] = 0;
	inds[1] = 1;
	inds[2] = 2;
	inds[3] = 3;
	inds[4] = 4;
	inds[5] = 5;

	Model::VertexLayout* vertices1 = new Model::VertexLayout[3];
	vertices1[0] = Model::VertexLayout(-0.9f, -0.5f, 0.0f, 1.0f, 0, 0);
	vertices1[1] = Model::VertexLayout(-0.0f, -0.5f, 0.0f, 0, 1.0f, 0);
	vertices1[2] = Model::VertexLayout(0.45f, 0.5f, 0.0f, 0, 0, 1.0f);

	Model::VertexLayout* vertices2 = new Model::VertexLayout[3];
	vertices2[3] = Model::VertexLayout(0.0f, -0.5f, 0.0f, 1.0f, 0, 0);
	vertices2[4] = Model::VertexLayout(0.9f, -0.5f, 0.0f, 0, 1.0f, 0);
	vertices2[5] = Model::VertexLayout(0.7f, 0.5f, 0.0f, 0, 0, 1.0f);

	Model* model1 = new Model();
	model1->SetVertices(vertices1, 3);
	model1->SetIndices(inds, 2);
	Model* model2 = new Model();
	model2->SetVertices(vertices2, 3);
	model2->SetIndices(inds, 2);

	//GLEW initialise
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	ShaderProgram* baseShaderProgram = new ShaderProgram();
	baseShaderProgram->ReadShaderFromPath("Shaders/BaseVert.hlsl", 0);
	baseShaderProgram->ReadShaderFromPath("Shaders/BaseFrag.hlsl", 1);
	baseShaderProgram->Init();
	baseShaderProgram->Compile();
	baseShaderProgram->Attach();

	baseShaderProgram->Link();

	model1->Init();
	model1->Bind();
	model1->Build();
	model1->Unbind();
	model2->Init();
	model2->Bind();
	model2->Build();
	model2->Unbind();

	//*****************************
	//SDL handled input
	//Any input to the program is done here

	SDL_Event event;
	bool windowOpen = true;

	while (windowOpen)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(baseShaderProgram->GetProgramID());
		model1->Bind();
		model1->Render();
		model1->Unbind();
		model2->Bind();
		model2->Render();
		model2->Unbind();
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

	delete baseShaderProgram;
	delete model1;
	delete model2;

	return 0;





}