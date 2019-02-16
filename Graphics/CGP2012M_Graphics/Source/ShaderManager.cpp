#include "ShaderManager.h"

namespace EngineOpenGL
{
	ShaderManager::ShaderManager()
	{
		ShaderProgram* baseShaderProgram = new ShaderProgram();
		baseShaderProgram->Init();
		baseShaderProgram->ReadShaderFromPath("Shaders/BaseVert.glsl", 0);
		baseShaderProgram->ReadShaderFromPath("Shaders/BaseFrag.glsl", 1);

		ShaderProgram* textureShaderProgram = new ShaderProgram();
		textureShaderProgram->Init();
		textureShaderProgram->ReadShaderFromPath("Shaders/TextureVert.glsl", 0);
		textureShaderProgram->ReadShaderFromPath("Shaders/TextureFrag.glsl", 1);

		this->shaders[0] = baseShaderProgram;
		this->shaders[1] = textureShaderProgram;
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
