#include "GameManager.h"
#include "SDL_image.h"
#include "SingletonManager.h"

namespace EngineOpenGL
{
	GameManager::GameManager()
	{
	}


	GameManager::~GameManager()
	{
		SDL_DestroyWindow(this->window);
		SDL_GL_DeleteContext(this->window);
		delete this->model1;
		SDL_Quit();
		IMG_Quit();
	}

	void GameManager::PreInitGL()
	{
		//set context attributes
		//sets opengl version to 4.3
		int major = 4, minor = 3;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE); //use core profile
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); //ask for forward compatible
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		this->glContext = SDL_GL_CreateContext(this->window);

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();

		//should build the manager;
		Singleton::getInstance();
	}

	void GameManager::PreInitSDL()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(SDL_INIT_EVERYTHING);
		this->window = SDL_CreateWindow("OpenGL Window", 100, 100, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	}

	void GameManager::Init()
	{
		this->model1 = new Model();
		//model1->SetModelToSquare(0.3f, 0.7f);
		model1->SetModelToCircle(0.5f);

		model1->Init();
		model1->Bind();
		model1->Build();
		model1->Unbind();

		this->texture = new TextureClass();
		this->texture->Bind();
		this->texture->LoadTexture("Textures/Test.png");
		this->texture->SetBuffers();
		this->texture->Unbind();
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		this->isRunning = true;
	}

	void GameManager::Update()
	{
	}

	void GameManager::Render()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		this->texture->Bind();
		glUseProgram(model1->GetShaderID());
		model1->Bind();
		model1->Render();
		model1->Unbind();
		SDL_GL_SwapWindow(this->window);
	}

	bool GameManager::GetIsRunning()
	{
		return this->isRunning;
	}
}