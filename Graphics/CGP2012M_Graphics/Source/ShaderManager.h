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
		ShaderProgram* GetShader(int key) const;
	};
}
#endif