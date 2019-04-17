#include "TextureClass.h"
#include <iostream>

namespace EngineOpenGL
{
	TextureClass::TextureClass()
	{
		glGenTextures(1, &this->textureID);
		this->surface = nullptr;
		this->name = std::string("null");
		this->type = EnumTextureTypes::TEXTURE_2D;
	}

	TextureClass::~TextureClass()
	{
		glDeleteTextures(1, &this->textureID);
	}
	
	void TextureClass::InitTexture2D(const std::vector<std::string>& paths)
	{
		this->LoadTexture(paths[0]);
		switch (this->surface->format->BytesPerPixel)
		{
		case 1:
			printf("ERROR! 8 bit depth cannot be handled!\n");
			break;
		case 2:
			printf("ERROR! 16 bit depth cannot be handled!\n");
			break;
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->surface->w, this->surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, this->surface->pixels);
			break;
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->surface->w, this->surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->surface->pixels);
			break;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void TextureClass::InitCubemap(const std::vector<std::string>& paths)
	{
		for (int i = 0; i < paths.size(); i++)
		{
			this->LoadTexture(paths[i]);
			switch (this->surface->format->BytesPerPixel)
			{
			case 1:
				printf("ERROR! 8 bit depth cannot be handled!\n");
				break;
			case 2:
				printf("ERROR! 16 bit depth cannot be handled!\n");
				break;
			case 3:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, this->surface->w, this->surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, this->surface->pixels);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, this->surface->w, this->surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->surface->pixels);
				break;
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	GLuint TextureClass::GetTextureID()
	{
		return this->textureID;
	}

	EnumTextureTypes TextureClass::GetTextureType() const
	{
		return this->type;
	}

	void TextureClass::LoadTexture(const std::string& path)
	{
		this->surface = IMG_Load(path.c_str());

		if (this->surface == NULL)
			std::cout << "Failed to load surface from " << path.c_str() << "!";
	}

	std::string TextureClass::GetName() const
	{
		return this->name;
	}

	void TextureClass::Init(const std::string& name, const std::vector<std::string>& paths, int& type)
	{
		this->name = name;
		this->type = (EnumTextureTypes)type;

		this->Bind();

		switch (this->type)
		{
		case EnumTextureTypes::TEXTURE_2D:
			this->InitTexture2D(paths);
			break;
		case EnumTextureTypes::CUBEMAP:
			this->InitCubemap(paths);
			break;
		default:
			break;
		}

		this->Unbind();
	}

	void TextureClass::Bind()
	{
		switch (this->type)
		{
		case EnumTextureTypes::TEXTURE_2D:
			glBindTexture(GL_TEXTURE_2D, this->textureID);
			break;
		case EnumTextureTypes::CUBEMAP:
			glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
			break;
		default:
			break;
		}
	}

	void TextureClass::Unbind()
	{
		switch (this->type)
		{
		case EnumTextureTypes::TEXTURE_2D:
			glBindTexture(GL_TEXTURE_2D, 0);
			break;
		case EnumTextureTypes::CUBEMAP:
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			break;
		default:
			break;
		}
	}
}