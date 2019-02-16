#include "ShaderManager.h"

namespace EngineOpenGL
{
	ShaderManager::ShaderManager()
	{
		ShaderProgram* baseShaderProgram = new ShaderProgram();
		baseShaderProgram->Init();
		baseShaderProgram->ReadShaderFromPath("Shaders/BaseVert.glsl", 0);
		baseShaderProgram->ReadShaderFromPath("Shaders/BaseFrag.glsl", 1);

		ShaderProgram* colorShaderProgram = new ShaderProgram();
		colorShaderProgram->Init();
		colorShaderProgram->ReadShaderFromPath("Shaders/ColourVert.glsl", 0);
		colorShaderProgram->ReadShaderFromPath("Shaders/ColourFrag.glsl", 1);

		this->shaders[0] = baseShaderProgram;
		this->shaders[1] = colorShaderProgram;
	}

	ShaderManager::~ShaderManager()
	{
		for (auto& x : this->shaders)
		{
			delete x.second;
		}
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
