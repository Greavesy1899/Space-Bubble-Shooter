#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H
#include <GL/glew.h>
#include "SDL.h"
#include "SDL_image.h"

namespace EngineOpenGL
{
	class TextureClass
	{
		SDL_Surface* surface;
		GLuint textureID;

	public:
		GLuint GetTextureID();
		void LoadTexture(const char* file);
		void SetBuffers();
		void Bind();
		void Unbind();
		TextureClass();
		~TextureClass();

	};
}
#endif