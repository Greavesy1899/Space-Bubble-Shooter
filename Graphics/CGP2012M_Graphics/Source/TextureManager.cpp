#include "TextureManager.h"
#include <map>
#include <tinyxml2.h>

using namespace tinyxml2;

namespace EngineOpenGL
{
	void TextureManager::AddTexture(int& id, const std::string& name, const std::vector<std::string>& paths, int& type)
	{
		TextureClass* texture = new TextureClass();
		texture->Init(name, paths, type);
		this->textures.insert(std::pair<int, TextureClass*>(id, texture));
	}

	void TextureManager::LoadTextureXML()
	{
		XMLDocument doc;
		doc.LoadFile("resource_textures.xml");

		if (doc.Error())
			printf("Error loading texture loader\n");

		XMLElement* node = doc.RootElement();

		if (strcmp(node->Attribute("version"), "1") != 0)
			printf("Old texture loader \n");

		for (const XMLElement* child = node->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			int id = child->IntAttribute("id");
			std::string name = child->Attribute("name");
			std::vector<std::string> paths = std::vector<std::string>();

			for (const XMLElement* pathNode = child->FirstChildElement(); pathNode != nullptr; pathNode = pathNode->NextSiblingElement())
					paths.push_back(pathNode->GetText());
				
			int type = child->IntAttribute("type");
			this->AddTexture(id, name, paths, type);
		}
	}

	TextureManager::TextureManager()
	{
		this->textures = std::map<int, TextureClass*>();
		LoadTextureXML();
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
		printf("Error! Did not find texture! Key is: %i \n", key);
		return this->textures.at(4);
	}
	TextureClass * TextureManager::GetTextureByName(const std::string & name) const
	{
		for (auto& x : this->textures)
		{
			if (x.second->GetName().compare(name))
				return x.second;
		}
		printf("Error! Did not find texture! Name is: %s \n", name.c_str());
		return this->textures.at(4);
	}
	int TextureManager::GetSize() const
	{
		return this->textures.size();
	}
}
