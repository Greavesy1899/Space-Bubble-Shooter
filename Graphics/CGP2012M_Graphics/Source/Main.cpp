#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>

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
#include "SZ_Timer.h"

using namespace EngineOpenGL;
SZ_Timer aTimer;

int main(int argc, char *argv[]) {
	srand(time(NULL));
	GameManager* gManager = new GameManager();
	gManager->PreInitSDL();
	gManager->PreInitGL();
	gManager->Init();

	//temp fix
	while (gManager->GetIsRunning())
	{
		aTimer.resetTicksTimer();
		gManager->Input();
		gManager->Update();
		gManager->Render();

		const int fps = 1000 / 60;
		if (aTimer.getTicks() < fps)
		{
			SDL_Delay(fps - aTimer.getTicks());
		}
	}
	delete gManager;
	return 0;
}