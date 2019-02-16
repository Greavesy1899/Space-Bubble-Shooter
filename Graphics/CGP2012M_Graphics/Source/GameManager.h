#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "SDL.h"
#include <GL/glew.h>
#include "ShaderProgram.h"
#include "Model.h"

namespace EngineOpenGL
{
	class GameManager
	{
		SDL_Window* window;
		SDL_GLContext glContext;
		Model* model1;
		TextureClass* texture;

		bool isRunning = false;

	public:
		GameManager();
		~GameManager();

		void PreInitGL();
		void PreInitSDL();
		void Init();
		void Update();
		void Render();

		bool GetIsRunning();
	};
}
#endif