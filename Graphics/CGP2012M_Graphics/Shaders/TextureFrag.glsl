#version 440 core
out vec4 vertColour;
in vec3 Colour;
in vec2 textureCoordinate;

uniform int renderType;
uniform sampler2D aTex;
uniform vec3 shapeColour;

void main()
{
	if(renderType == 0)
	{
		vertColour = texture(aTex, textureCoordinate);
	}
	else if(renderType == 1)
	{
		vertColour = vec4(Colour, 1.0f);
	}
	else if(renderType == 2)
	{
		vertColour = vec4(shapeColour, 1.0f);
	}


} 