#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <map>

#include "TextureClass.h"

namespace EngineOpenGL
{
	class TextureManager
	{
		std::map<int, TextureClass*> textures;

		void AddTexture(int, const char*); //only called during build phase.
	public:
		TextureManager();
		~TextureManager();
		TextureManager(const TextureManager& sm) = delete;
		TextureManager(TextureManager &&sm) = delete;

		//operators
		TextureManager operator=(const TextureManager& sm) = delete;
		TextureManager operator=(TextureManager& sm) = delete;

		TextureClass* GetTexture(int key) const;

	};
}
#endif