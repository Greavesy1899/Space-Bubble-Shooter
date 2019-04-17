#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H
#include <GL/glew.h>
#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"

namespace EngineOpenGL
{
	enum EnumTextureTypes
	{
		TEXTURE_2D,
		CUBEMAP,
	};

	class TextureClass
	{
		SDL_Surface* surface;
		GLuint textureID;
		std::string name;
		EnumTextureTypes type;

		void InitTexture2D(const std::vector<std::string>& paths);
		void InitCubemap(const std::vector<std::string>& paths);

	public:
		GLuint GetTextureID();
		EnumTextureTypes GetTextureType() const;
		void LoadTexture(const std::string& paths);
		std::string GetName() const;
		void Init(const std::string& name, const std::vector<std::string>& paths, int& type);
		void Bind();
		void Unbind();
		TextureClass();
		~TextureClass();

	};
}
#endif