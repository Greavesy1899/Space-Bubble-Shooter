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

void setColor(glm::vec3 vec) {
	glClearColor(vec[0], vec[1], vec[2], 1);
	glClear(GL_COLOR_BUFFER_BIT);
}
void overTimeColor() {
	//glClearColor(r, g, b, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
}
void changeColor() {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	glClearColor(r, g, b, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

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

	//****************************
	// OpenGL calls.
	glm::vec3 colour;
	colour[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	colour[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	colour[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	setColor(colour);
	SDL_GL_SwapWindow(win);


	//*****************************
	//SDL handled input
	//Any input to the program is done here

	SDL_Event event;
	bool windowOpen = true;

	bool switcherooR = false;
	bool switcherooG = false;
	bool switcherooB = false;

	while (windowOpen)
	{
		if (colour[0] <= 0.0f)
			switcherooR = true;
		else if (colour[0] >= 1.0f)
			switcherooR = false;
		if (colour[1] <= 0.0f)
			switcherooG = true;
		else if (colour[1] >= 1.0f)
			switcherooG = false;
		if (colour[2] <= 0.0f)
			switcherooB = true;
		else if (colour[2] >= 1.0f)
			switcherooB = false;

		if (switcherooR)
			colour[0] += 0.01f;
		else
			colour[0] -= 0.01;
		if (switcherooG)
			colour[1] += 0.01f;
		else
			colour[1] -= 0.01;
		if (switcherooB)
			colour[2] += 0.01f;
		else
			colour[2] -= 0.01;

		setColor(colour);
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