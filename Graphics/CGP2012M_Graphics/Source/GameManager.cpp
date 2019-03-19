#include "GameManager.h"
#include "SDL_image.h"
#include "SingletonManager.h"
#include "OBJLoader.h"

namespace EngineOpenGL
{
	void GameManager::updateScreen(int width, int height)
	{
		this->scene->UpdateCamera(width, height);
	}

	GameManager::GameManager()
	{
		this->scene = new Scene();
	}


	GameManager::~GameManager()
	{
		SDL_DestroyWindow(this->window);
		SDL_GL_DeleteContext(this->window);
		delete this->scene;
		SDL_Quit();
		IMG_Quit();
	}

	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		std::string errMessage = "Debug Message: ";
		errMessage += "Type: ";

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:
			errMessage += "Error";
			break;
		case GL_DEBUG_TYPE_OTHER:
			errMessage += "Other";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			errMessage += "Deprecated";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			errMessage += "Performance";
			break;
		}

		errMessage += "Severity: ";
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			errMessage += "High";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			errMessage += "Low";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			errMessage += "Medium";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			errMessage += "Notification";
		}
		errMessage += " ";
		errMessage += message;

		std::cout << errMessage << std::endl;
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

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//should build the manager;
		Singleton::getInstance();
	}

	void GameManager::PreInitSDL(int width, int height)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(SDL_INIT_EVERYTHING);

		GLint windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
		this->windowSize = glm::vec2(width / 2, height / 2);
		this->window = SDL_CreateWindow("Connor Greaves, CGP2012M, 17643079", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windowSize.x, this->windowSize.y, windowFlags);
		this->scene->UpdateCamera(this->windowSize.x, this->windowSize.y);
	}

	void GameManager::Init()
	{
		this->scene->Init();
		updateScreen(this->windowSize.x, this->windowSize.y);
		this->isRunning = true;
	}

	void GameManager::Input()
	{
		Singleton::getInstance()->GetIM()->ClearKeyVector();
		SDL_Event event;
		while (SDL_PollEvent(&event) == 1)
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				Singleton::getInstance()->GetIM()->AddKeyToVector(event.key.keysym.scancode);
				break;
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
						SDL_SetWindowSize(window, event.window.data1, event.window.data2);
						this->updateScreen(event.window.data1, event.window.data2);
					break;
				}
				break;
			default:
				break;
			}
		}

		if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_ESCAPE))
			isRunning = false;

		if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_P))
		{
			if (!this->isFullscreen)
			{
				SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				this->isFullscreen = true;
			}
			else
			{
				SDL_SetWindowFullscreen(this->window, 0);
				SDL_SetWindowSize(this->window, this->windowSize.x, this->windowSize.y);
				SDL_SetWindowBordered(this->window, SDL_TRUE);
				SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
				updateScreen(this->windowSize.x, this->windowSize.y);
				this->isFullscreen = false;
			}
		}

		scene->Input();
	}

	void GameManager::Update()
	{
		scene->Update();
	}

	void GameManager::Render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		scene->Render();	
		SDL_GL_SwapWindow(this->window);
	}

	bool GameManager::GetIsRunning()
	{
		return this->isRunning;
	}
}