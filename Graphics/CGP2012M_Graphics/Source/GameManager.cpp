#include "GameManager.h"
#include "SDL_image.h"
#include "SingletonManager.h"

namespace EngineOpenGL
{
	void GameManager::updateScreen(int width, int height)
	{
		//bugged as shit.
		//glm::mat4 proj = glm::perspective(45.0f, (float)width / height, 0.1f, 1000.0f);
		//glViewport(0, 0, width, height);
		//glMatrixMode(GL_PROJECTION);
		//glLoadMatrixf(glm::value_ptr(proj));
		//glMatrixMode(GL_MODELVIEW);
	}

	GameManager::GameManager()
	{
		this->models = std::vector<Model*>();
	}


	GameManager::~GameManager()
	{
		SDL_DestroyWindow(this->window);
		SDL_GL_DeleteContext(this->window);

		for (int i = 0; i != this->models.size(); i++)
			delete this->models[i];
		this->models.clear();

		delete this->texture;
		SDL_Quit();
		IMG_Quit();
	}

	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
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

		//should build the manager;
		Singleton::getInstance();
	}

	void GameManager::PreInitSDL()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(SDL_INIT_EVERYTHING);
		this->window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	}

	void GameManager::Init()
	{
		Model* model = new Model();
		model->SetModelToCircle(0.25f);
		model->Init();
		model->Bind();
		model->Build();
		model->Unbind();
		model->Transform.SetPosition(glm::vec3(-0.5f, 0.5f, 0.0f));

		Model* model1 = new Model();
		model1->SetModelToCircle(0.25f);
		model1->Init();
		model1->Bind();
		model1->Build();
		model1->Unbind();
		model1->Transform.SetPosition(glm::vec3(0.5f, -0.5f, 0.0f));
		this->models.push_back(model);
		this->models.push_back(model1);

		this->texture = new TextureClass();
		this->texture->Bind();
		this->texture->LoadTexture("Textures/Test.png");
		this->texture->SetBuffers();
		this->texture->Unbind();
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);


		

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
			case SDL_WINDOWEVENT_RESIZED:
				SDL_SetWindowSize(window, event.window.data1, event.window.data2);
				this->updateScreen(event.window.data1, event.window.data2);
				break;
			//case SDL_MOUSEMOTION:
			//	pos = Vector(event.motion.x, event.motion.y);
			//	Singleton::getInstance()->GetIM()->SetMousePos(pos);
			//	break;
			default:
				break;
			}
		}

		if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_ESCAPE))
			isRunning = false;
	}

	void GameManager::Update()
	{
		for (Model* model : this->models)
		{
			model->Transform.Translate(glm::vec3(0.0f, -0.01f, 0.0f));
		}
	}

	void GameManager::Render()
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (Model* model : this->models)
		{      
			model->LinkShader();
			model->Bind();
			model->Bind();
			glUseProgram(model->GetShaderID());
			GLint uniformLoc = glGetUniformLocation(model->GetShaderID(), "enableTex");
			GLint worldMatrixLoc = glGetUniformLocation(model->GetShaderID(), "WorldMatrix");
			glProgramUniform1i(model->GetShaderID(), uniformLoc, 0);
			glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, glm::value_ptr(model->Transform.GetMatrix()));
			model->Render();
			model->Unbind();
			model->DetachShader();
		}
		SDL_GL_SwapWindow(this->window);
	}

	bool GameManager::GetIsRunning()
	{
		return this->isRunning;
	}
}