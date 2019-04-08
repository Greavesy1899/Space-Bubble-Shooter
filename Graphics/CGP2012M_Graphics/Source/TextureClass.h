#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H
#include <GL/glew.h>
#include <string>
#include "SDL.h"
#include "SDL_image.h"

namespace EngineOpenGL
{
	class TextureClass
	{
		SDL_Surface* surface;
		GLuint textureID;
		std::string name;

	public:
		GLuint GetTextureID();
		void LoadTexture(const std::string& path);
		std::string GetName() const;
		void SetName(const std::string& name);
		void SetBuffers();
		void Bind();
		void Unbind();
		TextureClass();
		~TextureClass();

	};
}
#endif