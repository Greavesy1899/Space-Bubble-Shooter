#include <cstdio>
#include <cstdlib>
#include <iostream>

// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#include <GL/glew.h>
#include "windows.h"

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#include "SDL.h"
//#include "SDL_mixer.h"
// "SDL_ttf.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameManager.h"

using namespace EngineOpenGL;

int main(int argc, char *argv[]) {
	GameManager* gManager = new GameManager();
	gManager->PreInitSDL();
	gManager->PreInitGL();
	gManager->Init();

	SDL_Event event;
	bool windowOpen = true;

	//temp fix
	while (gManager->GetIsRunning() && windowOpen)
	{
		gManager->Render();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				windowOpen = false;
			}
		}
	}
	delete gManager;
	return 0;
}