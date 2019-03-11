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
		glDeleteTextures(1, &this->textureID);
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
		switch (this->surface->format->BytesPerPixel)
		{
		case 1:
			printf("ERROR! 8 bit depth cannot be handled!");
			break;
		case 2:
			printf("ERROR! 16 bit depth cannot be handled!");
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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