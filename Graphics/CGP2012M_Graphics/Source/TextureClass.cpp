#include "TextureClass.h"
#include <iostream>

namespace EngineOpenGL
{
	TextureClass::TextureClass()
	{
		glGenTextures(1, &this->textureID);
	}

	TextureClass::~TextureClass()
	{
	}

	GLuint TextureClass::GetTextureID()
	{
		return this->textureID;
	}

	void TextureClass::LoadTexture(const char * file)
	{
		this->surface = IMG_Load(file);

		if (this->surface == NULL)
			std::cout << "Failed to load surface from " << file << "!";
	}

	void TextureClass::SetBuffers()
	{
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->surface->w, this->surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, this->surface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void TextureClass::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}

	void TextureClass::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}