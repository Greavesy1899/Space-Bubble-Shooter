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

	Model* model = new Model();

	//GLEW initialise
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	ShaderProgram* baseShaderProgram = new ShaderProgram();
	baseShaderProgram->ReadShaderFromPath("Shaders/BaseVert.hlsl", 0);
	baseShaderProgram->ReadShaderFromPath("Shaders/BaseFrag.hlsl", 1);
	baseShaderProgram->Init();
	baseShaderProgram->Compile();
	baseShaderProgram->Attach();
	baseShaderProgram->Link();

	model->Init();
	model->Bind();
	model->Build();
	model->Unbind();

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
		model->Bind();
		model->Render();
		model->Unbind();
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
	delete model;

	return 0;





}