#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "SDL.h"
#include <GL/glew.h>
#include "ShaderProgram.h"
#include "Model.h"

class GameManager
{
	SDL_Window* window;
	SDL_GLContext glContext;

	ShaderProgram* baseShaderProgram;
	ShaderProgram* colorShaderProgram;
	Model* model1;

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
#endif

