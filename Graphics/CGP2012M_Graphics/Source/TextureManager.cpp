#include "TextureManager.h"

#include <map>
namespace EngineOpenGL
{
	void TextureManager::AddTexture(int id, const char * name)
	{
		TextureClass* texture = new TextureClass();
		texture->Bind();
		texture->LoadTexture(name);
		texture->SetBuffers();
		texture->Unbind();
		this->textures.insert(std::pair<int, TextureClass*>(id, texture));
	}

	TextureManager::TextureManager()
	{
		this->textures = std::map<int, TextureClass*>();
		this->AddTexture(0, "Textures/Test.png");
		this->AddTexture(1, "Textures/Bubble.png");
		this->AddTexture(2, "Textures/Background.png");
		this->AddTexture(3, "Textures/Heart.png");
	}

	TextureManager::~TextureManager()
	{
		for (auto& x : this->textures)
			delete x.second;

		this->textures.clear();
	}

	TextureClass * TextureManager::GetTexture(int key) const
	{
		for (auto& x : this->textures)
		{
			if (x.first == key)
				return x.second;
		}
		printf("Error! Did not find texture!\n");
		return nullptr;
	}
	int TextureManager::GetSize() const
	{
		return this->textures.size();
	}
}
