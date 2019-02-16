#ifndef SINGLETONMANAGER_H
#define SINGLETONMANAGER_H
#include "ShaderManager.h"

namespace EngineOpenGL
{
	class Singleton
	{
	private:
		static Singleton* instance;

		ShaderManager* sm;
	public:
		static Singleton* getInstance();

		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		ShaderManager* GetSM() const;

	private:
		Singleton();
		~Singleton();
	};
}
#endif