#include "SingletonManager.h"

namespace EngineOpenGL
{
	Singleton* Singleton::instance = nullptr;
	Singleton* Singleton::getInstance()
	{
		if (instance == nullptr)
			instance = new Singleton();

		return instance;
	}

	Singleton::~Singleton()
	{
		delete this->instance;
	}
	ShaderManager * Singleton::GetSM() const
	{
		return this->sm;
	}
	Singleton::Singleton()
	{
		this->sm = new ShaderManager();
	}
}