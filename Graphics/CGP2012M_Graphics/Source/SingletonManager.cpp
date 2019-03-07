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
		delete this->sm;
		delete this->im;
		delete this->tm;
		delete this->instance;
	}
	ShaderManager * Singleton::GetSM() const
	{
		return this->sm;
	}
	InputManager * Singleton::GetIM() const
	{
		return this->im;
	}
	TextureManager * Singleton::GetTM() const
	{
		return this->tm;
	}
	Singleton::Singleton()
	{
		this->sm = new ShaderManager();
		this->im = new InputManager();
		this->tm = new TextureManager();
	}
}