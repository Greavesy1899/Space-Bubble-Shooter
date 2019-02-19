#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <map>

#include "ShaderProgram.h"

namespace EngineOpenGL
{
	class ShaderManager
	{
		std::map<int, ShaderProgram*> shaders;

	public:
		ShaderManager();
		~ShaderManager();
		ShaderManager(const ShaderManager& sm) = delete;
		ShaderManager(ShaderManager &&sm) = delete;

		//operators
		ShaderManager operator=(const ShaderManager& sm) = delete;
		ShaderManager operator=(ShaderManager& sm) = delete;

		ShaderProgram* GetShader(int key) const;
	};
}
#endif