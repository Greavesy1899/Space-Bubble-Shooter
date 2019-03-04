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

void GetDesktopResolution(int& height, int& width)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	width = desktop.right;
	height = desktop.bottom;
}

int main(int argc, char *argv[]) {
	int height = 0;
	int width = 0;
	GetDesktopResolution(height, width);

	srand(time(NULL));
	GameManager* gManager = new GameManager();
	gManager->PreInitSDL(width, height);
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