#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <GL/glew.h>

#include "SDL.h"
#include "ShaderProgram.h"
#include "BubbleObject.h"

namespace EngineOpenGL
{
	class GameManager
	{
		SDL_Window* window;
		SDL_GLContext glContext;
		std::vector<BubbleObject*> models;
		TextureClass* texture;

		bool isRunning = false;
		void updateScreen(int width, int height);

	public:
		//constructor/destructor
		GameManager();
		~GameManager();
		GameManager(const GameManager& gm) = delete;
		GameManager(GameManager &&gm) = delete;

		//operators
		GameManager operator=(const GameManager& gm) = delete;
		GameManager operator=(GameManager& gm) = delete;

		//functions.
		void PreInitGL();
		void PreInitSDL();
		void Init();
		void Input();
		void Update();
		void Render();


		//accessors.
		bool GetIsRunning();
	};
}
#endif