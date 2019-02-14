#include "GameManager.h"
#include "SDL_image.h"

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	SDL_DestroyWindow(this->window);
	SDL_GL_DeleteContext(this->window);
	delete this->baseShaderProgram;
	delete this->colorShaderProgram;
	delete this->model1;
	delete this->model2;
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
}

void GameManager::PreInitSDL()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow("OpenGL Window", 100, 100, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
}

void GameManager::Init()
{
	this->baseShaderProgram = new ShaderProgram();
	//baseShaderProgram->Init();
	//baseShaderProgram->ReadShaderFromPath("Shaders/BaseVert.hlsl", 0);
	//baseShaderProgram->ReadShaderFromPath("Shaders/BaseFrag.hlsl", 1);
	//baseShaderProgram->Attach();
	//baseShaderProgram->Link();

	this->colorShaderProgram = new ShaderProgram();
	colorShaderProgram->Init();
	colorShaderProgram->ReadShaderFromPath("Shaders/ColourVert.hlsl", 0);
	colorShaderProgram->ReadShaderFromPath("Shaders/ColourFrag.hlsl", 1);
	colorShaderProgram->Attach();
	colorShaderProgram->Link();

	GLushort* inds = new GLushort[3];
	inds[0] = 0;
	inds[1] = 1;
	inds[2] = 2;

	Model::VertexLayout* vertices1 = new Model::VertexLayout[3];
	vertices1[0] = Model::VertexLayout(-0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	vertices1[1] = Model::VertexLayout(-0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	vertices1[2] = Model::VertexLayout(0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f);

	Model::VertexLayout* vertices2 = new Model::VertexLayout[3];
	vertices2[0] = Model::VertexLayout(0.0f, -0.5f, 0.0f, 1.0f, 0, 0, 1.0f, 1.0f);
	vertices2[1] = Model::VertexLayout(0.9f, -0.5f, 0.0f, 0, 1.0f, 0, 1.0f, 0.0f);
	vertices2[2] = Model::VertexLayout(0.7f, 0.5f, 0.0f, 0, 0, 1.0f, 0.5f, 0.5f);

	this->model1 = new Model();
	model1->SetVertices(vertices1, 3);
	model1->SetIndices(inds, 2);
	this->model2 = new Model();
	model2->SetVertices(vertices2, 3);
	model2->SetIndices(inds, 2);

	model1->Init();
	model1->Bind();
	model1->Build();
	model1->Unbind();
	model2->Init();
	model2->Bind();
	model2->Build();
	model2->Unbind();

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
	glUseProgram(this->colorShaderProgram->GetProgramID());
	model1->Bind();
	model1->Render();
	model1->Unbind();
	model2->Bind();
	model2->Render();
	model2->Unbind();
	SDL_GL_SwapWindow(this->window);
}

bool GameManager::GetIsRunning()
{
	return this->isRunning;
}
