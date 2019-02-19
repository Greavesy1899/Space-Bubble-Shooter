#ifndef SINGLETONMANAGER_H
#define SINGLETONMANAGER_H
#include "ShaderManager.h"
#include "InputManager.h"

namespace EngineOpenGL
{
	class Singleton
	{
	private:
		static Singleton* instance;

		ShaderManager* sm;
		InputManager* im;
	public:
		static Singleton* getInstance();

		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		ShaderManager* GetSM() const;
		InputManager* GetIM() const;

	private:
		Singleton();
		~Singleton();
	};
}
#endif