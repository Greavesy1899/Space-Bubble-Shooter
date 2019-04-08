#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <map>

#include "TextureClass.h"

namespace EngineOpenGL
{
	class TextureManager
	{
		std::map<int, TextureClass*> textures;

		void AddTexture(int, const std::string&, const std::string&); //only called during build phase.
		void LoadTextureXML();
	public:
		TextureManager();
		~TextureManager();
		TextureManager(const TextureManager& sm) = delete;
		TextureManager(TextureManager &&sm) = delete;

		//operators
		TextureManager operator=(const TextureManager& sm) = delete;
		TextureManager operator=(TextureManager& sm) = delete;


		TextureClass* GetTexture(int key) const;
		TextureClass* GetTextureByName(const std::string& name) const;
		int GetSize() const;

	};
}
#endif