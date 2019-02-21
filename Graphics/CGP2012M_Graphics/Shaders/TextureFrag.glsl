#version 440 core
out vec4 vertColour;
in vec3 Colour;
in vec2 textureCoordinate;

uniform int enableTex;

uniform sampler2D aTex;

void main()
{
	if(enableTex == 1)
	{
		vertColour = texture(aTex, textureCoordinate);
	}
	else
	{
		vertColour = vec4(Colour, 1.0f);
	}


} 