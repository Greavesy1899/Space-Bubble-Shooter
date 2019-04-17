#include "ShaderManager.h"

namespace EngineOpenGL
{
	ShaderManager::ShaderManager()
	{
		ShaderProgram* textureShaderProgram = new ShaderProgram();
		textureShaderProgram->Init();
		textureShaderProgram->ReadShaderFromPath("Shaders/TextureVert.glsl", 0);
		textureShaderProgram->ReadShaderFromPath("Shaders/TextureFrag.glsl", 1);
		ShaderProgram* skyboxShaderProgram = new ShaderProgram();
		skyboxShaderProgram->Init();
		skyboxShaderProgram->ReadShaderFromPath("Shaders/SkyboxVert.glsl", 0);
		skyboxShaderProgram->ReadShaderFromPath("Shaders/SkyboxFrag.glsl", 1);

		this->shaders[0] = textureShaderProgram;
		this->shaders[1] = skyboxShaderProgram;
	}

	ShaderManager::~ShaderManager()
	{
		for (auto& x : this->shaders)
			delete x.second;

		this->shaders.clear();
	}

	ShaderProgram * ShaderManager::GetShader(int key) const
	{
		for (auto& x : this->shaders)
		{
			if (x.first == key)
				return x.second;
		}
		printf("Error! Did not find shader!\n");
		return nullptr;
	}
}
